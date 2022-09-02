#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = 0;

  // create well known pipe
  int res = mkfifo(WKP, 0664);
  if (res == -1) printf("mkfifo error %d: %s\n", errno, strerror(errno));
  else printf("[server] created wkp\n");

  from_client = open(WKP, O_RDONLY);
  if (res == -1) printf("open error %d: %s\n", errno, strerror(errno));

  char buf[HANDSHAKE_BUFFER_SIZE];
  res = read(from_client, buf, sizeof(buf));
  if (res == -1) printf("read error %d: %s\n", errno, strerror(errno));
  else printf("[server] read [%s]\n", buf);

  remove(WKP);
  printf("removed "WKP"\n");

  // printf("[%s]\n", buf);
  *to_client = open(buf, O_WRONLY);
  if (*to_client == -1) printf("open error %d: %s\n", errno, strerror(errno));
  else printf("[server] connected to [%s]\n", buf);

  char syn_ack[10] = "hello";
  res = write(*to_client, syn_ack, sizeof(syn_ack));
  if (*to_client == -1) printf("write error %d: %s\n", errno, strerror(errno));
  else printf("[server] sent syn_ack [%s]\n", syn_ack);

  char ack[10];
  res = read(from_client, ack, sizeof(ack));
  if (res == -1) printf("read error %d: %s\n", errno, strerror(errno));
  else printf("[server] read [%s]\n", ack);


  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server = 0;

  char private_buf[HANDSHAKE_BUFFER_SIZE];
  sprintf(private_buf, "%d", getpid());

  int res = mkfifo(private_buf, 0664);
  if (res == -1) printf("mkfifo error %d: %s\n", errno, strerror(errno));
  else printf("[client] created private\n");

  *to_server = open(WKP, O_WRONLY);
  if (*to_server == -1) printf("open error %d: %s\n", errno, strerror(errno));
  else printf("[client] connected to ["WKP"]\n");

  res = write(*to_server, private_buf, sizeof(private_buf));
  if (res == -1) printf("write error %d: %s\n", errno, strerror(errno));
  else printf("[client] wrote [%s] to server\n", private_buf);

  from_server = open(private_buf, O_RDONLY);
  char syn_ack[10];
  res = read(from_server, syn_ack, sizeof(syn_ack));
  if (res == -1) printf("read error %d: %s\n", errno, strerror(errno));
  else printf("[client] read [%s] from server\n", syn_ack);


  remove(private_buf);
  printf("removed %s\n", private_buf);

  res = write(*to_server, ACK, 10);
  if (res == -1) printf("write error %d: %s\n", errno, strerror(errno));
  else printf("[client] wrote ["ACK"] to server\n");

  
  return from_server;
}
