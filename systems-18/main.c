#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

void to_lower_case(char* str);

int main() {

  int pw_fds[2];
  int cw_fds[2];

  pipe(pw_fds);
  pipe(cw_fds);

  // printf("pw pipe created. fd[READ]: %d, fd[WRITE]: %d\n", pw_fds[READ], pw_fds[WRITE]);

  int f = fork();
  
  if (f) {
    close(pw_fds[READ]);
    close(cw_fds[WRITE]);
    while (1) {
      printf("input: ");
      char buf[256];
      fgets(buf, sizeof(buf), stdin);
      write(pw_fds[WRITE], buf, sizeof(buf));
      char new_buf[1024];
      read(cw_fds[READ], new_buf, sizeof(new_buf));
      printf("all lower: %s", new_buf);
     }
  }
  else {
    close(pw_fds[WRITE]);
    close(cw_fds[READ]);
    char input_buf[256];
    while(read(pw_fds[READ], input_buf, sizeof(input_buf))) {
      to_lower_case(input_buf);
      write(cw_fds[WRITE], input_buf, sizeof(input_buf));
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
