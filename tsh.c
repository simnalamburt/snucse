//
// tsh - A tiny shell program with job control
//
// 2013-11392, Hyeon Kim
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
#define MAXJID    1<<16   // max job ID

// Job states
#define UNDEF 0 // undefined
#define FG 1    // running in foreground
#define BG 2    // running in background
#define ST 3    // stopped

//
// Jobs states: FG (foreground), BG (background), ST (stopped)
// Job state transitions and enabling actions:
//     FG -> ST  : ctrl-z
//     ST -> FG  : fg command
//     ST -> BG  : bg command
//     BG -> FG  : fg command
// At most 1 job can be in the FG state.
//

// Global variables
extern char **environ;      // defined in libc
char prompt[] = "tsh> ";    // command line prompt (DO NOT CHANGE)
int verbose = 0;            // if true, print additional output
int nextjid = 1;            // next job ID to allocate
char sbuf[MAXLINE];         // for composing sprintf messages

struct job_t {              // The job struct
  pid_t pid;                // job PID
  int jid;                  // job ID [1, 2, ...]
  int state;                // UNDEF, BG, FG, or ST
  char cmdline[MAXLINE];    // command line
};
struct job_t jobs[MAXJOBS]; // The job list
// End global variables


// Function prototypes

// Here are the functions that you will implement
void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

// Here are helper routines that we've provided for you
int parseline(const char *cmdline, char **argv);
void sigquit_handler(int sig);

void clearjob(struct job_t *job);
void initjobs(struct job_t *jobs);
int maxjid(struct job_t *jobs);
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline);
int deletejob(struct job_t *jobs, pid_t pid);
pid_t fgpid(struct job_t *jobs);
struct job_t *getjobpid(struct job_t *jobs, pid_t pid);
struct job_t *getjobjid(struct job_t *jobs, int jid);
int pid2jid(pid_t pid);
void listjobs(struct job_t *jobs);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);

//
// main - The shell's main routine
//
int main(int argc, char **argv) {
  char c;
  char cmdline[MAXLINE];
  int emit_prompt = 1; // emit prompt (default)

  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  dup2(1, 2);

  // Parse the command line
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h':           // print help message
      usage();
      break;
    case 'v':           // emit additional diagnostic info
      verbose = 1;
      break;
    case 'p':           // don't print a prompt
      emit_prompt = 0;  // handy for automatic testing
      break;
    default:
      usage();
    }
  }

  // Install the signal handlers

  // These are the ones you will need to implement
  Signal(SIGINT,  sigint_handler);   // ctrl-c
  Signal(SIGTSTP, sigtstp_handler);  // ctrl-z
  Signal(SIGCHLD, sigchld_handler);  // Terminated or stopped child

  // This one provides a clean way to kill the shell
  Signal(SIGQUIT, sigquit_handler);

  // Initialize the job list
  initjobs(jobs);

  // Execute the shell's read/eval loop
  while (true) {
    // Read command line
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }
    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
      app_error("fgets error");
    if (feof(stdin)) { // End of file (ctrl-d)
      fflush(stdout);
      exit(0);
    }

    // Evaluate the command line
    eval(cmdline);
    fflush(stdout);
    fflush(stdout);
  }

  exit(0); // control never reaches here
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

  pid_t pid = fork();

  // Codes for child process
  if (!pid) {
    // Set pgid as 0
    setpgid(0, 0);
    execve(argv[0], argv, environ);

    // `execve` returns only on error cases
    printf("%s: Command not found\n", argv[0]);
    exit(1);
  }

  if (is_foreground) {
    addjob(jobs, pid, FG, cmdline);
    // Wait until foreground job finishes
    waitfg(pid);
  } else {
    addjob(jobs, pid, BG, cmdline);
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
int parseline(const char *cmdline, char **argv) {
  static char array[MAXLINE];   // holds local copy of command line
  char *buf = array;            // ptr that traverses command line
  char *delim;                  // points to first space delimiter
  int argc;                     // number of args
  int bg;                       // background job?

  strcpy(buf, cmdline);
  buf[strlen(buf)-1] = ' ';     // replace trailing '\n' with space
  while (*buf && (*buf == ' ')) // ignore leading spaces
    buf++;

  // Build the argv list
  argc = 0;
  if (*buf == '\'') {
    buf++;
    delim = strchr(buf, '\'');
  } else {
    delim = strchr(buf, ' ');
  }

  while (delim) {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;

    // ignore spaces
    while (*buf && (*buf == ' ')) { buf++; }

    if (*buf == '\'') {
      buf++;
      delim = strchr(buf, '\'');
    } else {
      delim = strchr(buf, ' ');
    }
  }
  argv[argc] = NULL;

  // ignore blank line
  if (argc == 0) { return 1; }

  // should the job run in the background?
  if ((bg = (*argv[argc-1] == '&')) != 0) {
    argv[--argc] = NULL;
  }
  return bg;
}

//
// If the user has typed a built-in command then execute it immediately.
//
int builtin_cmd(char *argv[]) {
  // Match argv[0] with build-in commands
  if (!strcmp(argv[0], "quit")) {
    // Exit
    exit(0);
  } else if (!strcmp(argv[0], "fg")) {
    // Call running background job to foreground
    do_bgfg(argv);
    return 1;
  } else if (!strcmp(argv[0], "bg")) {
    // Resume stopped background job
    do_bgfg(argv);
    return 1;
  } else if (!strcmp(argv[0], "jobs")) {
    // List all jobs
    listjobs(jobs);
    return 1;
  } else {
    // argv[0] is not a built-in command
    return 0;
  }
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
  struct job_t *p_job;

  char *p = strstr(argv[1], "%");
  if (p) {
    // argv[1] was '%<jobid>'
    int jobid = atoi(p + 1);
    p_job = getjobjid(jobs, jobid);

    if (!p_job) {
      printf("%%%d: No such job\n", jobid);
      return;
    }

    pid = p_job->pid;
  } else if (isdigit(argv[1][0])) {
    // argv[1] was '<pid>'
    pid = atoi(argv[1]);
    p_job = getjobpid(jobs, pid);

    if (!p_job) {
      printf("(%d): No such process\n", pid);
      return;
    }
  } else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]);
    return;
  }

  // Resume the stopped execution
  kill(-pid, SIGCONT);

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
  struct job_t *p_job = getjobpid(jobs, pid);
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
  int status = -1;
  pid_t pid;
  while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
    // Check how given process is terminated or stopped
    struct job_t *p_job = getjobpid(jobs, pid);

    if (WIFEXITED(status)) {
      // Exited normally, print no message
      deletejob(jobs,pid);
    } else if (WIFSIGNALED(status)) {
      // Terminated with signal
      printf("Job [%d] (%d) terminated by signal 2\n", p_job->jid, p_job->pid);
      deletejob(jobs,pid);
    } else if (WIFSTOPPED(status)) {
      // Stopped by signal
      printf("Job [%d] (%d) stopped by signal 20\n", p_job->jid, p_job->pid);
      p_job->state = ST;
    }
  }
}

// Catch ^C (SIGINT) and send it to the foreground job.
void sigint_handler(int sig) {
  pid_t pid = fgpid(jobs);
  if (pid) { kill(-pid, SIGINT); }
}

// Catch ^Z (SIGTSTP) and send it to the foreground job.
void sigtstp_handler(int sig) {
  pid_t pid = fgpid(jobs);
  if (pid) { kill(-pid, SIGTSTP); }
}


//
// End signal handlers
//



//
// Helper routines that manipulate the job list
//

// Clear the entries in a job struct
void clearjob(struct job_t *job) {
  job->pid = 0;
  job->jid = 0;
  job->state = UNDEF;
  job->cmdline[0] = '\0';
}

// Initialize the job list
void initjobs(struct job_t *jobs) {
  int i;

  for (i = 0; i < MAXJOBS; i++) {
    clearjob(&jobs[i]);
  }
}

// Returns largest allocated job ID
int maxjid(struct job_t *jobs) {
  int i, max=0;

  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].jid > max)
      max = jobs[i].jid;
  return max;
}

// Add a job to the job list
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline)
{
  int i;

  if (pid < 1)
    return 0;

  for (i = 0; i < MAXJOBS; i++) {
    if (jobs[i].pid == 0) {
      jobs[i].pid = pid;
      jobs[i].state = state;
      jobs[i].jid = nextjid++;
      if (nextjid > MAXJOBS)
        nextjid = 1;
      strcpy(jobs[i].cmdline, cmdline);
      if(verbose){
        printf("Added job [%d] %d %s\n", jobs[i].jid, jobs[i].pid, jobs[i].cmdline);
      }
      return 1;
    }
  }
  printf("Tried to create too many jobs\n");
  return 0;
}

// deletejob - Delete a job whose PID=pid from the job list
int deletejob(struct job_t *jobs, pid_t pid)
{
  int i;

  if (pid < 1)
    return 0;

  for (i = 0; i < MAXJOBS; i++) {
    if (jobs[i].pid == pid) {
      clearjob(&jobs[i]);
      nextjid = maxjid(jobs)+1;
      return 1;
    }
  }
  return 0;
}

// fgpid - Return PID of current foreground job, 0 if no such job
pid_t fgpid(struct job_t *jobs) {
  int i;

  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].state == FG)
      return jobs[i].pid;
  return 0;
}

// getjobpid  - Find a job (by PID) on the job list
struct job_t *getjobpid(struct job_t *jobs, pid_t pid) {
  int i;

  if (pid < 1)
    return NULL;
  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].pid == pid)
      return &jobs[i];
  return NULL;
}

// getjobjid  - Find a job (by JID) on the job list
struct job_t *getjobjid(struct job_t *jobs, int jid) {
  int i;

  if (jid < 1)
    return NULL;
  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].jid == jid)
      return &jobs[i];
  return NULL;
}

// pid2jid - Map process ID to job ID
int pid2jid(pid_t pid) {
  int i;

  if (pid < 1)
    return 0;
  for (i = 0; i < MAXJOBS; i++)
    if (jobs[i].pid == pid) {
      return jobs[i].jid;
    }
  return 0;
}

// listjobs - Print the job list
void listjobs(struct job_t *jobs) {
  int i;

  for (i = 0; i < MAXJOBS; i++) {
    if (jobs[i].pid != 0) {
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
}


//
// Other helper routines
//

// Print a help message
void usage(void)
{
  printf("Usage: shell [-hvp]\n");
  printf("   -h   print this message\n");
  printf("   -v   print additional diagnostic information\n");
  printf("   -p   do not emit a command prompt\n");
  exit(1);
}

// Unix-style error routine
void unix_error(char *msg)
{
  fprintf(stdout, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

// Application-style error routine
void app_error(char *msg) {
  fprintf(stdout, "%s\n", msg);
  exit(1);
}

// wrapper for the sigaction function
handler_t *Signal(int signum, handler_t *handler) {
  struct sigaction action, old_action;

  action.sa_handler = handler;
  sigemptyset(&action.sa_mask); // block sigs of type being handled
  action.sa_flags = SA_RESTART; // restart syscalls if possible

  if (sigaction(signum, &action, &old_action) < 0)
    unix_error("Signal error");
  return (old_action.sa_handler);
}

// SIGQUIT signal handler
void sigquit_handler(int sig) {
  printf("Terminating after receipt of SIGQUIT signal\n");
  exit(1);
}
