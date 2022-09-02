#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <signal.h>

#include "editor.h"

#ifndef CONSOLE_H
#define CONSOLE_H

#define KEY 24602
#define READ 0
#define WRITE 1
#define OUTPUT_LEN 1024

WINDOW *open_console(int start_y);
WINDOW *open_output(int start_y);
char *read_console_input(WINDOW *win, char *input, int *mode, int *console_y);
int run_command(char *command, char *output, char *content, char *filename, int fs);
char **split(char *input, char *tok);

#endif