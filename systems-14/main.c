#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


static void sighandler(int signo) {
    if (signo == SIGINT) {
        int fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd == -1) {
            printf("error %d: %s\n", errno, strerror(errno));
            return;
        }
        char buffer[] = "Program exited due to SIGINT\n";
        int res = write(fd, buffer, sizeof(buffer));
        if (res == -1) {
            printf("error %d: %s\n", errno, strerror(errno));
            return;
        }
        exit(0);
    }
    if (signo == SIGUSR1) {
        printf("parent pid: %d\n", getppid());
    }
}

int main() {
    
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    while (1) {
        printf("running process\tid:%d\n", getpid());
        sleep(1);
    }

    return 0;
}