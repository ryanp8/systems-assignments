#include "console.h"

WINDOW *open_console(int start_y) {
    WINDOW *win = newwin(0, 0, start_y, 0);
    keypad(win, TRUE);
    return win;
}

WINDOW *open_output(int start_y) {
    WINDOW *win = newwin(0, 0, start_y, 0);
    keypad(win, TRUE);
    return win;
}

char *read_console_input(WINDOW *win, char *input, int *mode, int* console_y) {
    echo();
    char *buf = malloc(1024);
    wgetstr(win, buf);
    return buf;
}


int run_command(char *command, char *output, char *content, char *filename, int fs) {

    if (strcmp(command, "write") == 0) {
        int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        write(fd, content, fs - 1);
        strcpy(output, "changes written!\n");
    }
    else if (strcmp(command, "quit") == 0) {
        kill(getpid(), 2);
    }
    else if (strcmp(command, "wq") == 0) {
        int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        write(fd, content, fs - 1);
        strcpy(output, "changes written!\n");
        kill(getpid(), 2);
    }
    else {
        char *tmp = malloc(OUTPUT_LEN);
        strcpy(tmp, command);
        char **parsed = split(tmp, " ");
        int stdout_dup = dup(STDOUT_FILENO);

        int fds[2];
        pipe(fds);
        int f = fork();
        if (f) {
            close(fds[WRITE]);
            read(fds[READ], output, OUTPUT_LEN);
        }
        else {
            close(fds[READ]);
            dup2(fds[WRITE], STDOUT_FILENO);
            int res = execvp(parsed[0], parsed);
        }
        dup2(stdout_dup, STDOUT_FILENO);

        if (strlen(output) < 1) {
            strcpy(output, "command not found!\n");
            return -1;
        }
        free(tmp);
        free(parsed);
    }
    
    return 0;
}

char **split(char *input, char *tok) {
    int tok_count = strcount(input, tok[0]);
    char **parsed = calloc(tok_count + 2, sizeof(char*));
    int i = 0;
    while(input) {
        parsed[i] = strsep(&input, tok);
        if (input) {
            input += strlen(tok) - 1;
        }
        i++;
    }
    return parsed;
}


