#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define KEY 24602

// union semun {
//   int val;                  //used for SETVAL
//   struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
//   unsigned short  *array;   //used for SETALL
//   struct seminfo  *__buf;
// };

char *get_previous(int data);
int write_data();


int main() {

    int semd = semget(KEY, 0, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;
    printf("waiting to access sem\n");
    semop(semd, &sb, 1);

    int shmd = shmget(KEY, 0, 0);
    int *data = shmat(shmd, 0, 0);

    char *prev = get_previous(*data);
    printf("previous entry: %s", prev);
    if (*data == 0) {
        printf("\n");
    }
    free(prev);

    int input_len = write_data();
    *data = input_len;

    shmdt(data);

    sb.sem_op = 1;
    semop(semd, &sb, 1);

    return 0;
}

char *get_previous(int data) {
    int fd = open("telephone.data", O_RDONLY);
    int l = lseek(fd, -data, SEEK_END);
    if (fd == -1) {
        printf("%s\n", strerror(errno));
    }
    char *buf = malloc(data);
    int res = read(fd, buf, data);
    if (res == -1) {
        printf("%s\n", strerror(errno));
    }
    close(fd);
    return buf;
}

int write_data() {
    int fd = open("telephone.data", O_WRONLY | O_APPEND);
    printf("new input: ");
    char new_buf[1024];
    fgets(new_buf, sizeof(new_buf), stdin);
    char len = strlen(new_buf);
    write(fd, new_buf, len);
    close(fd);
    return len;
}
