#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main() {
    printf("parent init\n");
    int f = fork();
    if (f) {
        f = fork();
    }
    if (f) {
        int w, status;
        w = wait(&status);
        printf("child pid: %d\tasleep for %d seconds\n", w, WEXITSTATUS(status));
        printf("parent process completed\n");
    }
    else {
        printf("child pid: %d\n", getpid());
        srand(time(NULL));
        int i;
        for (i = 0; i < getpid() % 10; i++) {
            rand();
        }
        int r = (int) ((float) (rand() % 100) / 100 * 4) + 2;
        sleep(r);
        printf("child process finished\n");
        return r;
    }
    
    return 0;
}