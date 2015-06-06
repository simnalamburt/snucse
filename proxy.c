//
// proxy.c - CS:APP Web proxy
//
// Student Information:
//     김지현, 2013-11392
//
// 0.  argv[1]에서 프록시를 작동시킬 포트 번호를 얻어낸다.
// 1.  소켓 하나를 초기화시켜 연결이 들어올때까지 기다린다.
// 2.  연결이 맺어질경우 "\r\n\r\n"을 받을때까지 읽어서 request header를 받는다.
//
// 3.  얻어낸 Request header에서, "Connection: keep-alive" 라는 문자열을 찾아
//     "Connection: close"로 치환한다. 이때 길이가 변하는데, memmove() 함수로
//     처리한다.
//
// 4.  Request header에 적혀있는 서버 URI를 hostname과 포트번호, path로
//     분리한다음, hostname에 대응되는 IP주소가 몇인지 DNS Lookup을 수행한다.
//
// 5.  DNS Lookup으로 알아낸 IP 주소를 통해, 웹서버와 커넥션을 맺는다. 버퍼에
//     저장된 Request header를 서버로 보낸다.
//
// 6.  웹서버가 연결을 종료할때까지 웹서버가 전송하는 모든 데이터를
//     클라이언트에게 보낸다.
//
// 1~6을 반복한다.
//
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <netdb.h>
#include <arpa/inet.h>

// Max text line length
#define MAXLINE 8192


//
// Global variable
//
static FILE *log;


//
// Function prototypes
//
typedef struct {
  int client;
  char addr_txt[INET_ADDRSTRLEN];
} data_t;

static void *per_connection(void *client);
static ssize_t read_all(int fd, void *buf, size_t bufsize);
static ssize_t read_header(int fd, void *buf, size_t bufsize);
static ssize_t write_all(int fd, const void *buf, size_t count);
static int parse_uri(char *uri, char *target_addr, int *port);


//
// 시스템콜 반환값 검사하는 함수.
//
static inline int yes(int ret) {
  if (ret != -1) { return ret; }
  perror("Critical error");
  exit(1);
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

  // Ignore SIGPIPE
  signal(SIGPIPE, SIG_IGN);

  // Open log file
  log = fopen("proxy.log", "a");

  // Initialize incoming socket
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof addr);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[1]));
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  const int sock = yes(socket(addr.sin_family, SOCK_STREAM, 0));

  const int opt = true;
  yes(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt));
  yes(bind(sock, (struct sockaddr*)&addr, sizeof addr));
  yes(listen(sock, SOMAXCONN));

  while (true) {
    // 클라이언트와 커넥션 맺을때까지 대기
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof client_addr;
    int client = accept(sock, (struct sockaddr*)&client_addr, &client_len);
    if (client == -1) { perror("accept"); continue; }

    // 로그
    data_t *data = malloc(sizeof(data_t));
    data->client = client;
    inet_ntop(client_addr.sin_family, &client_addr.sin_addr, data->addr_txt, sizeof data->addr_txt);

    // 처리
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t thread;
    pthread_create(&thread, &attr, per_connection, data);
  }

  // Release resources
  yes(close(sock));
  yes(fclose(log));
  return 0;
}


//
// 한 커넥션마다 실행될 함수
//
void *per_connection(void *_data) {
  data_t *data = _data;
  int client = data->client;

  // Initialize read/write buffer
  size_t bufsize = 2 * 1024 * 1024;
  void *const buf = malloc(bufsize);

  // Read header
  ssize_t count = read_header(client, buf, bufsize);

  // "Connection: keep-alive" -> "Connection: close"
  char needle[] = "Connection: keep-alive\r\n";
  size_t needle_len = sizeof needle - 1;
  void *pos = memmem(buf, count, needle, needle_len);
  if (pos != NULL) {
    char overwrite[] = "Connection: close\r\n";
    size_t overwrite_len = sizeof overwrite - 1;
    memcpy(pos, overwrite, overwrite_len);

    void *end = (void*)((uintptr_t)pos + overwrite_len);
    void *next = (void*)((uintptr_t)pos + needle_len);
    size_t remain = (uintptr_t)buf + bufsize - (uintptr_t)next;
    memmove(end, next, remain);
    bufsize -= needle_len - overwrite_len;
  }

  // Extract URI
  char *uri_begin = memmem(buf, count, "http://", 7);
  char *uri_end = memchr(uri_begin, ' ', bufsize - ((uintptr_t)uri_begin - (uintptr_t)buf));
  size_t uri_len = (uintptr_t)uri_end - (uintptr_t)uri_begin;
  char uri[MAXLINE] = {};
  memcpy(uri, uri_begin, uri_len);

  // Parse URI
  char hostname[MAXLINE] = {};
  int port, ret;
  ret = parse_uri(uri, hostname, &port);
  if (ret == -1) { fprintf(stderr, "  There was no \"http://\" on the first line of the payload\n"); goto free_buf; }

  // DNS Lookup
  struct addrinfo *result;
  ret = getaddrinfo(hostname, NULL, NULL, &result);
  if (ret) { fprintf(stderr, "getaddrinfo() Failed\n"); goto free_buf; }

  // Set port number
  struct sockaddr_in *addr = (struct sockaddr_in*)result->ai_addr;
  addr->sin_port = htons(port);

  // Make a new connection toward the server
  const int server = socket(result->ai_family, result->ai_socktype, 0);
  if (server == -1) { perror("socket"); goto free_result; }
  ret = connect(server, result->ai_addr, result->ai_addrlen);
  if (ret == -1) { perror("connect"); goto close_server; }

  // Upload the request header
  ret = write_all(server, buf, count);
  if (ret == -1) { perror("write_all"); goto close_server; }

  // Download the response
  size_t size = 0;
  while (true) {
    count = read_all(server, buf, bufsize);
    if (count == 0) { break; }
    ret = write_all(client, buf, count);
    if (ret == -1) { perror("write_all"); goto close_server; }
    size += count;
  }

  // Log
  time_t now = time(NULL);
  char time_str[MAXLINE];
  strftime(time_str, MAXLINE, "%a %d %b %y %h:%m:%s %z", localtime(&now));

  fprintf(log, "%s: %s %s %lu\n", time_str, data->addr_txt, uri, size);
  fflush(log);

close_server:
  close(server);
free_result:
  freeaddrinfo(result);
free_buf:
  free(buf);
  close(client);
  free(data);
  return NULL;
}



//
// 주어진 버퍼가 다 차거나, fd에서 EOF를 줄때까지 읽기를 계속한다.
//
// If return value == bufsize, the buffer is full
// Otherwise, met EOF or error
//
// 스레드세이프함.
//
static ssize_t read_all(int fd, void *buf, size_t bufsize) {
  void *current = buf;
  size_t remain = bufsize;

  do {
    ssize_t count = read(fd, current, remain);
    if (count == 0 || count == -1) { break; }

    remain -= count;
    current = (void*)((uintptr_t)current + count);
  } while (remain > 0);
  return bufsize - remain;
}


//
// 주어진 버퍼가 다 차거나, fd에서 EOF나 "CRLFCRLF"를 줄때까지 읽기를 계속한다.
//
// If return value == bufsize, the buffer is full
// Otherwise, met EOF, "CRLFCRLF" or error
//
// 스레드세이프함.
//
static ssize_t read_header(int fd, void *buf, size_t bufsize) {
  void *current = buf;
  size_t remain = bufsize;
  bool end = false;

  do {
    ssize_t count = read(fd, current, remain);
    if (count == 0 || count == -1) { break; }

    void *pos = memmem(current, count, "\r\n\r\n", 4);
    if (pos != NULL) { end = true; }

    remain -= count;
    current = (void*)((uintptr_t)current + count);
  } while (remain > 0 && !end);
  return bufsize - remain;
}


//
// 버퍼에 있는 모든 내용물을 fd에 쓴다.
//
// If return value == count, successfully wrote everything
// Otherwise, error
//
// 스레드세이프함.
//
static ssize_t write_all(int fd, const void *buf, size_t count) {
  const void *current = buf;
  size_t remain = count;

  do {
    ssize_t count = write(fd, current, remain);
    if (count == -1) { return -1; }

    remain -= count;
    current = (void*)((uintptr_t)current + count);
  } while (remain > 0);
  return count - remain;
}


//
// parse_uri - URI parser
//
// Given a URI from an HTTP proxy GET request (i.e., a URL), extract the host
// name and port. The memory for hostname must already be allocated and should
// be at least MAXLINE bytes. Return -1 if there are any problems.
//
// 스레드세이프함.
//
int parse_uri(char *uri, char *hostname, int *port) {
  if (uri == NULL || strncasecmp(uri, "http://", 7) != 0) {
    hostname[0] = '\0';
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
  if (*hostend == ':') { *port = atoi(hostend + 1); }

  return 0;
}
