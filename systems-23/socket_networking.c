#include "socket_networking.h"


/*=========================
  server_setup
  args:
  creates the WKP (upstream) and opens it, waiting for a
  connection.
  removes the WKP once a connection has been made
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int sd;
  struct addrinfo *hints, *results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;

  getaddrinfo("127.0.0.1", "9845", hints, &results);
  sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  printf("[server] create socket\n");
  if (sd == -1) {
    printf("creating socket error %d: %s\n", errno, strerror(errno));
    exit(-1);
  }
  bind(sd, results->ai_addr, results->ai_addrlen);
  printf("[server] bind socket\n");

  listen(sd, 10);
  printf("[server] listening\n");

  free(hints);
  freeaddrinfo(results);

  return sd;
}

/*=========================
  server_connect
  args: int from_client
  handles the subserver portion of the 3 way handshake
  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int client_socket = 0;
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  client_socket = accept(from_client, (struct sockaddr *)&client_address, &sock_size);

  return client_socket;
}


int client_connect() {
  int sd;
  struct addrinfo *hints, *results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;

  getaddrinfo("127.0.0.1", "9845", hints, &results);
  sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  printf("[client] create socket\n");
  if (sd == -1) {
    printf("creating socket error %d: %s\n", errno, strerror(errno));
    exit(-1);
  }
  connect(sd, results->ai_addr, results->ai_addrlen);
  printf("[client] connected\n");
  return sd;
}

