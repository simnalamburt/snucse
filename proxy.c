//
// proxy.c - CS:APP Web proxy
//
// Student Information:
//     김지현, 2013-11392
//
// 0.  argv[1]에서 프록시를 작동시킬 포트 번호를 얻어낸다.
// 1.  소켓 하나를 초기화시켜 연결이 들어올때까지 기다린다.
// 2.  연결이 맺어질경우 맨 첫번째줄만 먼저 읽은다음 거기서 URI를 얻어낸다.
//     얻어낸 URI를 hostname과 포트번호, path로 분리한다음, hostname에 대응되는
//     IP주소가 몇인지 DNS Lookup을 수행한다.
// 3.  freeaddrinfo() 를 호출해 DNS Lookup 결과를 정리한다.
// 4.  클라이언트쪽 소켓으로부터 EOF에 도달할때까지 모든 정보를 읽어서, 2번에서
//     읽었던 첫번째줄 뒤에 붙인다. 이것으로 클라이언트가 전송한 온전한
//     payload를 버퍼에 저장하였다.
// 5.  클라이언트와 연결을 종료한다.
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
#include <netdb.h>
#include <arpa/inet.h>

// Max text line length
#define MAXLINE 8192


//
// Function prototypes
//
static int parse_uri(char *uri, char *target_addr, char *path, int *port);
static void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, const char *uri, size_t size);


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

  while (true) {
    // 클라이언트와 커넥션 맺을때까지 대기
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client = accept(sock, (struct sockaddr*)&client_addr, &client_len);
    if (client == -1) { perror("accept"); continue; }
    printf("Connection established with \e[36m%s:%d\e[0m\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Convert fd into FILE*
    FILE *input = fdopen(client, "r");

    // Read first line
    fgets(buf, bufsize, input);

    // Parse URI
    char hostname[MAXLINE] = {};
    char path[MAXLINE] = {};
    int port;
    ret = parse_uri(strstr(buf, "http://"), hostname, path, &port);
    if (ret != -1) {
      // DNS Lookup
      struct addrinfo *result;
      ret = getaddrinfo(hostname, NULL, NULL, &result);
      if (ret) { fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret)); continue; }

      // Set port number
      struct sockaddr_in *addr = (struct sockaddr_in*)result->ai_addr;
      addr->sin_port = htons(port);

      // Print lookup result
      printf("hostname : %s\n", hostname);
      printf("host IP  : %s\n", inet_ntoa(addr->sin_addr));
      printf("port     : %d\n", ntohs(addr->sin_port));
      printf("path     : %s\n", path);

      // Make a new connection toward the server
      const int sock = socket(result->ai_family, result->ai_socktype, 0);
      if (sock == -1) { perror("socket"); continue; }
      ret = connect(sock, result->ai_addr, result->ai_addrlen);
      if (ret == -1) { perror("connect"); continue; }

      // Deallocate DNS Lookup result
      freeaddrinfo(result);

      // Close the server socket
      ret = close(sock);
      if (ret == -1) { perror("close"); continue; }
    } else {
      fprintf(stderr, "parse_uri: There was no \"http://\" on the first line of the payload\n");
    }

    // Read the rest
    size_t len = strlen(buf);
    size_t count = len + fread((void*)((uintptr_t)buf + len), 1, bufsize - len, input);


    // Print payload
    printf("\e[32m");
    fwrite(buf, 1, count, stdout);
    fflush(stdout);
    printf("\e[0m\n(%ld bytes)\n", count);


    // Close the connection
    ret = fclose(input);
    if (ret) { perror("fclose"); continue; }
    printf("Closed connection with \e[36m%s:%d\e[0m\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
  }

  // Release resources
  free(buf);
  ret = close(sock);
  if (ret == -1) { perror("close"); return -1; }

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
  if (uri == NULL || strncasecmp(uri, "http://", 7) != 0) {
    hostname[0] = '\0';
    pathname[0] = '\0';
    return -1;
  }

  // Extract the host name
  char *hostbegin = uri + 7;
  char *hostend = strpbrk(hostbegin, " :/\r\n\0");
  int len = hostend - hostbegin;
  strncpy(hostname, hostbegin, len);
  hostname[len] = '\0';

  // Extract the port number
  *port = 80;
  if (*hostend == ':') {
    *port = atoi(hostend + 1);
  }

  // Extract the path
  char *pathbegin = strchr(hostbegin, '/');
  if (pathbegin == NULL) {
    pathname[0] = '/';
    pathname[1] = '\0';
  } else {
    char *pathend = strpbrk(pathbegin, " \r\n\0");
    strncpy(pathname, pathbegin, (uintptr_t)pathend - (uintptr_t)pathbegin);
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
