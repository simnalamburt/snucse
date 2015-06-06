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
static void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, char *uri, size_t size);


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
  uint32_t a = ntohl(addr.sin_addr.s_addr);
  printf("Listening on \e[33m%d.%d.%d.%d:%d\e[0m ...\n\n",
      a >> 24, (a >> 16) & 0xff, (a >> 8) & 0xff, a & 0xff, ntohs(addr.sin_port));

  do {
    struct sockaddr client;
    socklen_t client_len;
    ret = accept(sock, &client, &client_len);
    if (ret == -1) { perror("accept"); continue; }

    ret = close(sock);
    if (ret == -1) { perror("close"); continue; }
  } while (false);

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
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, char *uri, size_t size) {
  time_t now;
  char time_str[MAXLINE];
  unsigned long host;
  unsigned char a, b, c, d;

  // Get a formatted time string
  now = time(NULL);
  strftime(time_str, MAXLINE, "%a %d %b %Y %H:%M:%S %Z", localtime(&now));

  //
  // Convert the IP address in network byte order to dotted decimal
  // form. Note that we could have used inet_ntoa, but chose not to
  // because inet_ntoa is a Class 3 thread unsafe function that
  // returns a pointer to a static variable (Ch 13, CS:APP).
  //
  host = ntohl(sockaddr->sin_addr.s_addr);
  a = host >> 24;
  b = (host >> 16) & 0xff;
  c = (host >> 8) & 0xff;
  d = host & 0xff;

  // Return the formatted log entry string
  sprintf(logstring, "%s: %d.%d.%d.%d %s %lu", time_str, a, b, c, d, uri, size);
}
