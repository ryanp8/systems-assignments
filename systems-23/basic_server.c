#include "socket_networking.h"

void to_lower_case(char *str);


int main() {
    int listening = server_setup();
    int client;

    while (1) {
      client = server_connect(listening);
      printf("forking\n");
      int f;
      f = fork();
      if (f) {
        close(client);
      }
      else {
        while (1) {
          char buf[BUFFER_SIZE];
          while (read(client, buf, sizeof(buf))) {
            to_lower_case(buf);
            write(client, buf, sizeof(buf));
          }
        }
      }
    }

    return 0;
}


void to_lower_case(char *str) {
  int i;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] >= 65 && str[i] <= 90) {
      str[i] += 32;
    }
  }
}