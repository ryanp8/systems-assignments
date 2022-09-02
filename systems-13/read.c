#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


#include "read.h"
#include "print.h"
#include "entry.h"

char **read_csv() {
    printf("reading nyc_pop.csv\n");
    int fd = open("nyc_pop.csv", O_RDONLY);
    struct stat s;
    stat("nyc_pop.csv", &s);

    char *buffer = malloc(s.st_size);
    int res = read(fd, buffer, s.st_size);
    if (res == -1) {
        print_error();
        return NULL;
    } 

    char **rows = split_rows(buffer, s.st_size);
    free(buffer);
    close(fd);
    return rows;
}

char **split_rows(char *data, int file_size) {
    char **arr = malloc(8 * num_rows());
    arr[0] = malloc(100);
    int current_row = 0;
    int row_pos = 0;
    int i;
    for (i = 0; i < file_size; i++) {
        if (data[i] == '\n') {
            current_row++;
            arr[current_row] = malloc(100);
            row_pos = 0;
        } 
        else {
            arr[current_row][row_pos] = data[i];
            row_pos++;
        }
    }

    return arr;
}


struct pop_entry *read_data() {
    int fd = open("nyc.data", O_RDONLY);
    int ds = data_size();
    struct pop_entry *entries = malloc(ds);
    int res = read(fd, entries, ds);
    if (res == -1) {
        print_error();
        return NULL;
    }

    close(fd);
    return entries;
}

int num_rows() {
    int fd = open("nyc_pop.csv", O_RDONLY);
    struct stat s;
    stat("nyc_pop.csv", &s);
    char *buffer = malloc(s.st_size);
    int res = read(fd, buffer, s.st_size);
    if (res == -1) {
        print_error();
        return -1;
    }

    int total = 0;
    int i;
    for (i = 0; i < s.st_size; i++) {
        if (buffer[i] == '\n') {
            total++;
        }
    }
    free(buffer);
    return total + 1;
}

int data_size() {
    struct stat s;
    stat("nyc.data", &s);
    return s.st_size;
}