//
// proxy.c - CS:APP Web proxy
//
// Student Information:
//     김지현, 2013-11392
//
// IMPORTANT: Give a high level description of your code here. You
// must also provide a header comment at the beginning of each
// function that describes what that function does.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Max text line length
#define MAXLINE 8192


//
// Function prototypes
//
static int parse_uri(char *uri, char *target_addr, char *path, int *port);
static void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, const char *uri, size_t size);


//
// 주어진 버퍼가 다 차거나, fd에서 EOF를 줄때까지 읽기를 계속한다. 이 함수의
// 실행결과는 아래 셋 중 하나이다
//
// 1. 버퍼가 꽉참
// 2. 다읽었음
// 3. 에러
//
static ssize_t read_all(int fd, void *buf, size_t size) {
  void *current = buf;
  size_t remain = size;

  do {
    ssize_t count = read(fd, current, remain);
    if (count == 0) { break; }
    if (count == -1) { return -1; }

    remain -= count;
    current = (void*)((uintptr_t)current + count);
  } while (remain > 0);

  return size - remain;
}


//
// Main routine for the proxy program
//
int main(int argc, char **argv) {
  // Check arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
    return 1;
  }

  int ret;

  // Initialize incoming socket
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[1]));
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  const int sock = socket(addr.sin_family, SOCK_STREAM, 0);
  if (sock == -1) { perror("socket"); return 1; }

  const int opt = true;
  ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  if (ret == -1) { perror("setsockopt"); return 1; }

  ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
  if (ret == -1) { perror("bind"); return 1; }

  ret = listen(sock, SOMAXCONN);
  if (ret == -1) { perror("listen"); return 1; }

  // Print message
  printf("Listening on \e[33m%s:%d\e[0m ...\n\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

  // Initialize read/write buffer
  const size_t bufsize = 100 * 1024; // 100KB
  void *const buf = malloc(bufsize);

  do {
    // 클라이언트와 커넥션 맺을때까지 대기
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client = accept(sock, (struct sockaddr*)&client_addr, &client_len);
    if (client == -1) { perror("accept"); continue; }
    printf("Connection established with \e[36m%s:%d\e[0m\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Read until EOF
    ssize_t count = read_all(client, buf, bufsize);
    if (count == -1) { perror("read"); continue; }

    // Print payload
    printf("\e[32m%.*s\e[0m\n", (int)count, (char*)buf);
    printf("(%ld bytes)\n", count);

    // Close socket
    ret = close(sock);
    if (ret == -1) { perror("close"); continue; }
    printf("Closed connection with \e[36m%s:%d\e[0m\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
  } while (false);

  // Deallocate buffer
  free(buf);

  return 0;
}


//
// parse_uri - URI parser
//
// Given a URI from an HTTP proxy GET request (i.e., a URL), extract
// the host name, path name, and port.  The memory for hostname and
// pathname must already be allocated and should be at least MAXLINE
// bytes. Return -1 if there are any problems.
//
int parse_uri(char *uri, char *hostname, char *pathname, int *port) {
  char *hostbegin;
  char *hostend;
  char *pathbegin;
  int len;

  if (strncasecmp(uri, "http://", 7) != 0) {
    hostname[0] = '\0';
    return -1;
  }

  // Extract the host name
  hostbegin = uri + 7;
  hostend = strpbrk(hostbegin, " :/\r\n\0");
  len = hostend - hostbegin;
  strncpy(hostname, hostbegin, len);
  hostname[len] = '\0';

  // Extract the port number
  *port = 80; // default
  if (*hostend == ':')
    *port = atoi(hostend + 1);

  // Extract the path
  pathbegin = strchr(hostbegin, '/');
  if (pathbegin == NULL) {
    pathname[0] = '\0';
  } else {
    pathbegin++;
    strcpy(pathname, pathbegin);
  }

  return 0;
}


//
// format_log_entry - Create a formatted log entry in logstring.
//
// The inputs are the socket address of the requesting client
// (sockaddr), the URI from the request (uri), and the size in bytes
// of the response from the server (size).
//
void format_log_entry(char *logstring, struct sockaddr_in *addr, const char *uri, size_t size) {
  // Get a formatted time string
  time_t now = time(NULL);
  char time_str[MAXLINE];
  strftime(time_str, MAXLINE, "%a %d %b %Y %H:%M:%S %Z", localtime(&now));

  // Return the formatted log entry string
  sprintf(logstring, "%s: %s %s %lu", time_str, inet_ntoa(addr->sin_addr), uri, size);
}
