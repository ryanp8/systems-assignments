#include "socket_networking.h"


int main() {

    // int to_server;
    // int from_server;

    int server = client_connect();

    while (1) {
        printf("input: ");
        char buf[BUFFER_SIZE];
        fgets(buf, sizeof(buf), stdin);
        write(server, buf, sizeof(buf));
        read(server, buf, sizeof(buf));
        printf("all lower: %s", buf);
    }

    return 0;
}