//
// tsh - A tiny shell program with job control
//
// 2013-11392, Hyeon Kim
//

//
// Jobs states: FG (foreground), BG (background), ST (stopped)
// Job state transitions and enabling actions:
//     FG -> ST  : ctrl-z
//     ST -> FG  : fg command
//     ST -> BG  : bg command
//     BG -> FG  : fg command
// At most 1 job can be in the FG state.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

// Misc manifest constants
#define MAXLINE    1024   // max line size
#define MAXARGS     128   // max args on a command line
#define MAXJOBS      16   // max jobs at any point in time

// Job status
typedef enum {
  UNDEF, // undefined
  FG, // running in foreground
  BG, // running in background
  ST, // stopped
} job_status;

// Job struct
typedef struct {
  pid_t pid;
  int jid; // Job ID (1, 2, ...)
  job_status state;
  char cmdline[MAXLINE]; // command line
} job_t;

extern char *environ[]; // defined in libc

// command line prompt (DO NOT CHANGE)
static char prompt[] = "tsh> ";
// if true, print additional output
static bool verbose = false;
// next job ID to allocate
static int nextjid = 1;

// The job list
static job_t jobs[MAXJOBS] = {};
static void addjob(pid_t pid, int state, char *cmdline);
static void deletejob(pid_t pid);
static pid_t fgpid();
static job_t *getjobpid(pid_t pid);
static job_t *getjobjid(int jid);
static int pid2jid(pid_t pid);
static void listjobs();


// Function prototypes
static void eval(char *cmdline);
static bool builtin_cmd(char *argv[]);
static void do_bgfg(char *argv[]);
static void waitfg(pid_t pid);

static void sigchld_handler(int sig);
static void sigtstp_handler(int sig);
static void sigint_handler(int sig);

static bool parseline(const char *cmdline, char *argv[]);
static void sigquit_handler(int sig);


static int check(int, const char *msg);

static void Signal(int signum, void (*handler)(int));

//
// main - The shell's main routine
//
int main(int argc, char *argv[]) {
  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  dup2(STDOUT_FILENO, STDERR_FILENO);

  // Parse the command line
  char c;
  bool emit_prompt = true;
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'v':           // emit additional diagnostic info
      verbose = true;
      break;
    case 'p':           // don't print a prompt
      emit_prompt = false;  // handy for automatic testing
      break;
    case 'h':           // print help message
    default:
      puts("Usage: shell [-hvp]\n"
           "    -h   print this message\n"
           "    -v   print additional diagnostic information\n"
           "    -p   do not emit a command prompt");
      exit(c != 'h');
    }
  }

  Signal(SIGINT,  sigint_handler);
  Signal(SIGTSTP, sigtstp_handler);
  Signal(SIGCHLD, sigchld_handler);
  Signal(SIGQUIT, sigquit_handler);

  // REPL
  while (true) {
    if (emit_prompt) {
      fputs(prompt, stdout);
      fflush(stdout);
    }

    // Read command line
    char cmdline[MAXLINE];
    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      puts("fgets() call failed");
      exit(1);
    }

    // Received EOF(^D)
    if (feof(stdin)) { break; }

    // Evaluate the command line
    eval(cmdline);
    fflush(stdout);
  }

  fflush(stdout);
  return 0;
}

//
// eval - Evaluate the command line that the user has just typed in
//
// If the user has requested a built-in command (quit, jobs, bg or fg)
// then execute it immediately. Otherwise, fork a child process and
// run the job in the context of the child. If the job is running in
// the foreground, wait for it to terminate and then return.  Note:
// each child process must have a unique process group ID so that our
// background children don't receive SIGINT (SIGTSTP) from the kernel
// when we type ctrl-c (ctrl-z) at the keyboard.
//
void eval(char *cmdline) {
  char *argv[MAXARGS];
  const bool is_foreground = !parseline(cmdline, argv);

  // Ignore empty input and built-in command
  if (!argv[0] || builtin_cmd(argv)) { return; }

  sigset_t set = {};
  check(sigemptyset(&set), "sigemptyset() failed");
  check(sigaddset(&set, SIGCHLD), "sigaddset() failed");
  check(sigprocmask(SIG_BLOCK, &set, NULL), "sigprocmask() failed");

  pid_t pid = check(fork(), "fork() system call failed");

  // Codes for child process
  if (!pid) {
    // Set pgid as 0
    check(setpgid(0, 0), "setpgid() system call failed");
    check(sigprocmask(SIG_UNBLOCK, &set, NULL), "sigprocmask() failed");
    execve(argv[0], argv, environ);
    // `execve` returns only on error cases
    printf("%s: Command not found\n", argv[0]);
    exit(1);
  }

  addjob(pid, is_foreground ? FG : BG, cmdline);
  check(sigprocmask(SIG_UNBLOCK, &set, NULL), "sigprocmask() failed");
  if (is_foreground) {
    // Wait until foreground job finishes
    waitfg(pid);
  } else {
    // Print information of the background job and proceed
    printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);
  }
}

//
// parseline - Parse the command line and build the argv array.
//
// Characters enclosed in single quotes are treated as a single
// argument.  Return true if the user has requested a BG job, false if
// the user has requested a FG job.
//
bool parseline(const char *cmdline, char *argv[]) {
  static char array[MAXLINE];   // holds local copy of command line
  char *buf = array;            // ptr that traverses command line

  strcpy(buf, cmdline);
  buf[strlen(buf)-1] = ' ';     // replace trailing '\n' with space
  while (*buf && (*buf == ' ')) // ignore leading spaces
    buf++;

  // Build the argv list
  int argc = 0;
  char *delim;                  // points to first space delimiter
  if (*buf == '\'') {
    ++buf;
    delim = strchr(buf, '\'');
  } else {
    delim = strchr(buf, ' ');
  }

  while (delim) {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;

    // ignore spaces
    while (*buf && (*buf == ' ')) { ++buf; }

    if (*buf == '\'') {
      ++buf;
      delim = strchr(buf, '\'');
    } else {
      delim = strchr(buf, ' ');
    }
  }
  argv[argc] = NULL;

  // ignore blank line
  if (argc == 0) { return true; }

  // should the job run in the background?
  bool bg = *argv[argc-1] == '&';
  if (bg) { argv[--argc] = NULL; }
  return bg;
}

//
// If the user has typed a built-in command then execute it immediately.
//
bool builtin_cmd(char *argv[]) {
  // Match argv[0] with build-in commands
  if (!strcmp(argv[0], "quit")) {
    // Exit
    exit(0);
  } else if (!strcmp(argv[0], "fg")) {
    // Call running background job to foreground
    do_bgfg(argv);
  } else if (!strcmp(argv[0], "bg")) {
    // Resume stopped background job
    do_bgfg(argv);
  } else if (!strcmp(argv[0], "jobs")) {
    // List all jobs
    listjobs();
  } else {
    // argv[0] is not a built-in command
    return false;
  }
  return true;
}

//
// Execute the builtin bg and fg commands
//
void do_bgfg(char *argv[]) {
  // Requires parameter
  if (!argv[1]) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }

  int pid;
  job_t *p_job;

  char *p = strstr(argv[1], "%");
  if (p) {
    // argv[1] was '%<jobid>'
    int jobid = atoi(p + 1);
    p_job = getjobjid(jobid);

    if (!p_job) {
      printf("%%%d: No such job\n", jobid);
      return;
    }

    pid = p_job->pid;
  } else if (isdigit(argv[1][0])) {
    // argv[1] was '<pid>'
    pid = atoi(argv[1]);
    p_job = getjobpid(pid);

    if (!p_job) {
      printf("(%d): No such process\n", pid);
      return;
    }
  } else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]);
    return;
  }

  // Resume the stopped execution
  check(kill(-pid, SIGCONT), "Failed to send SIGCONT signal");

  if (!strcmp(argv[0], "fg")) {
    p_job->state = FG;
    // Wait until foreground job finishes
    waitfg(pid);
  } else {
    p_job->state = BG;
    // Print information of the background job and proceed
    printf("[%d] (%d) %s", p_job->jid, p_job->pid, p_job->cmdline);
  }
}

//
// Block until process pid is no longer the foreground process
//
void waitfg(pid_t pid) {
  job_t *p_job = getjobpid(pid);
  if (!p_job) { return; }
  // Busy wait until p_job goes to background or finishes
  while (p_job->state == FG) { sleep(1); }
}


//
// Signal handlers
//

//
// sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//     a child job terminates (becomes a zombie), or stops because it
//     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//     available zombie children, but doesn't wait for any other
//     currently running children to terminate.
//
void sigchld_handler(int sig) {
  int status;
  pid_t pid;
  while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
    // Check how given process is terminated or stopped
    job_t *p_job = getjobpid(pid);

    if (WIFEXITED(status)) {
      // Exited normally, print no message
      deletejob(pid);
    } else if (WIFSIGNALED(status)) {
      // Terminated with signal
      printf("Job [%d] (%d) terminated by signal 2\n", p_job->jid, p_job->pid);
      deletejob(pid);
    } else if (WIFSTOPPED(status)) {
      // Stopped by signal
      printf("Job [%d] (%d) stopped by signal 20\n", p_job->jid, p_job->pid);
      p_job->state = ST;
    }
  }
  if (errno == ECHILD) { return; }
  check(pid, "waitpid() system call failed");
}

// Catch ^C (SIGINT) and send it to the foreground job.
void sigint_handler(int sig) {
  pid_t pid = fgpid();
  if (!pid) { return; }
  check(kill(-pid, SIGINT), "Failed to send SIGINT signal");
}

// Catch ^Z (SIGTSTP) and send it to the foreground job.
void sigtstp_handler(int sig) {
  pid_t pid = fgpid();
  if (!pid) { return; }
  check(kill(-pid, SIGTSTP), "Failed to send SIGTSTP signal");
}



//
// Helper routines that manipulate the job list
//

// Add a job to the job list
void addjob(pid_t pid, int state, char *cmdline) {
  if (pid <= 0) { return; }

  int i;
  for (i = 0; i < MAXJOBS; ++i) {
    if (jobs[i].pid) { continue; }

    jobs[i].pid = pid;
    jobs[i].state = state;
    jobs[i].jid = nextjid++;
    strcpy(jobs[i].cmdline, cmdline);
    if (nextjid > MAXJOBS) { nextjid = 1; }
    if (verbose) {
      printf("Added job [%d] %d %s\n", jobs[i].jid, jobs[i].pid, jobs[i].cmdline);
    }
    return;
  }
  check(-1, "Job list overflow");
}

// deletejob - Delete a job whose PID=pid from the job list
void deletejob(pid_t pid) {
  // Reject negative pid
  if (pid <= 0) { return; }

  // Find target job object with pid
  int i;
  for (i = 0; i < MAXJOBS; ++i) {
    if (jobs[i].pid != pid) { continue; }

    // Delete found job
    memset(&jobs[i], 0, sizeof jobs[i]);

    // Update nextjid as 'max(jid) + 1'
    nextjid = 0;
    for (i = 0; i < MAXJOBS; ++i) {
      if (jobs[i].jid <= nextjid) { continue; }
      nextjid = jobs[i].jid;
    }
    ++nextjid;
    return;
  }
}

// fgpid - Return PID of current foreground job, 0 if no such job
pid_t fgpid() {
  int i;
  for (i = 0; i < MAXJOBS; ++i) {
    if (jobs[i].state != FG) { continue; }
    return jobs[i].pid;
  }

  return 0;
}

// getjobpid  - Find a job (by PID) on the job list
job_t *getjobpid(pid_t pid) {
  if (pid <= 0) { return NULL; }

  int i;
  for (i = 0; i < MAXJOBS; ++i) {
    if (jobs[i].pid != pid) { continue; }
    return &jobs[i];
  }

  return NULL;
}

// getjobjid  - Find a job (by JID) on the job list
job_t *getjobjid(int jid) {
  if (jid <= 0) { return NULL; }

  int i;
  for (i = 0; i < MAXJOBS; ++i) {
    if (jobs[i].jid != jid) { continue; }
    return &jobs[i];
  }

  return NULL;
}

// pid2jid - Map process ID to job ID
int pid2jid(pid_t pid) {
  job_t *p_job = getjobpid(pid);
  return p_job ? p_job->jid : 0;
}

// listjobs - Print the job list
void listjobs() {
  int i;
  for (i = 0; i < MAXJOBS; ++i) {
    if (!jobs[i].pid) { continue; }

    printf("[%d] (%d) ", jobs[i].jid, jobs[i].pid);
    switch (jobs[i].state) {
    case BG:
      printf("Running ");
      break;
    case FG:
      printf("Foreground ");
      break;
    case ST:
      printf("Stopped ");
      break;
    default:
      printf("listjobs: Internal error: job[%d].state=%d ", i, jobs[i].state);
    }
    printf("%s", jobs[i].cmdline);
  }
}


//
// Other helper routines
//

int check(int ret, const char* msg) {
  if (ret != -1) { return ret; }
  printf("%s: %s\n", msg, strerror(errno));
  exit(1);
}

// wrapper for the sigaction function
void Signal(int signum, void (*handler)(int)) {
  struct sigaction new, old;
  new.sa_handler = handler;
  new.sa_flags = SA_RESTART; // restart syscalls if possible
  sigemptyset(&new.sa_mask); // block sigs of type being handled
  check(sigaction(signum, &new, &old), "Signal error");
}

// SIGQUIT signal handler
void sigquit_handler(int _) {
  puts("Terminating after receipt of SIGQUIT signal");
  exit(1);
}
