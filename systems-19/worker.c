#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void to_lower_case(char *str);

int main() {
    int named1_fd;
    named1_fd = open("named1", O_WRONLY);
    printf("pipe1 connected\n");

    int named2_fd;
    named2_fd = open("named2", O_RDONLY);
    printf("pipe2 connected\n");

    char buf[1024];
    while (read(named2_fd, buf, sizeof(buf))) {
        to_lower_case(buf);
        write(named1_fd, buf, sizeof(buf));
    }


    close(named1_fd);
    close(named2_fd);
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