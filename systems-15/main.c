#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char **parse_args(char *line) {
    char **args = malloc(5);
    char *token;
    int i = 0;
    while (line) {
        token = strsep(&line, " ");
        args[i] = token;
        i++;
    }
    return args;
}

int main() {
    char line[100] = "ls -l";

    char ** args = parse_args( line );
    execvp(args[0], args);
    free(args);

    return 0;
}