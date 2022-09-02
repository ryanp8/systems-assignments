#include "pipe_networking.h"


int main() {

    int to_server;
    int from_server;

    from_server = client_handshake( &to_server );

    while (1) {
        printf("input: ");
        char buf[BUFFER_SIZE];
        fgets(buf, sizeof(buf), stdin);
        write(to_server, buf, sizeof(buf));
        read(from_server, buf, sizeof(buf));
        printf("all lower: %s", buf);
    }

    return 0;
}