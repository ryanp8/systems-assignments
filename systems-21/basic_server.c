#include "pipe_networking.h"

void to_lower_case(char *str);


int main() {
    int to_client;
    int from_client;

    from_client = server_handshake( &to_client );

    while (1) {
        char buf[BUFFER_SIZE];
        while (read(from_client, buf, sizeof(buf))) {
            to_lower_case(buf);
            write(to_client, buf, sizeof(buf));
        }
        from_client = server_handshake( &to_client );
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