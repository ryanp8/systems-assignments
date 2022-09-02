#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define KEY 24602

// union semun {
//   int val;                  //used for SETVAL
//   struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
//   unsigned short  *array;   //used for SETALL
//   struct seminfo  *__buf;
// };

void print_story();

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
            printf("creating file\n");
            int fd = open("telephone.data", O_CREAT | O_TRUNC, 0664);
            if (fd == -1) {
                printf("%s\n", strerror(errno));
            }
            int shmd;
            int semd;
            
            printf("creating shm\n");
            shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
            if (shmd == -1) {
                printf("error %d: %s\n", errno, strerror(errno));
            }
            printf("creating sem\n");
            semd = semget(KEY, 1, IPC_EXCL | IPC_CREAT | 0644);
            if (semd == -1) {
                printf("error %d: %s\n", errno, strerror(errno));
            }
            else {
                union semun us;
                us.val = 1;
                int r = semctl(semd, 0, SETVAL, us);   
            }

        }
        else if (strcmp(argv[1], "-v") == 0) {
            printf("removing\n");

            int shmd = shmget(KEY, 0, 0);
            int semd = semget(KEY, 0, 0);

            printf("removing shm\n");
            shmctl(shmd, IPC_RMID, 0);

            printf("removing sem\n");
            semctl(semd, IPC_RMID, 0);
            print_story();
        }
    }
    return 0;
}

void print_story() {
    int fd = open("telephone.data", O_RDONLY);
    struct stat sb;
    stat("telephone.data", &sb);
    char *contents = malloc(sb.st_size);
    read(fd, contents, sb.st_size);
    printf("\nStory so far:\n%s", contents);
    free(contents);
    close(fd);
}