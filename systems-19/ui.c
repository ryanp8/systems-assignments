#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {

    mkfifo("named1", 0644);
    mkfifo("named2", 0644);

    
    int named1_fd;
    named1_fd = open("named1", O_RDONLY);
    printf("pipe1 connected\n");

    int named2_fd;
    named2_fd = open("named2", O_WRONLY);
    printf("pipe2 connected\n");

    
    while (1) {
        printf("input: ");
        char buf[256];
        fgets(buf, sizeof(buf), stdin);
        write(named2_fd, buf, sizeof(buf));
        char new_buf[1024];
        read(named1_fd, new_buf, sizeof(new_buf));
        printf("all lower: %s", new_buf);
    }
    


    close(named1_fd);
    close(named2_fd);

    return 0;
}


