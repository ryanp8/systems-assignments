#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define ARRAY_LEN 10

int generate_random(int fd) {
    int buff[1];
    read(fd, buff, sizeof(int));
    if (errno) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }
    return *buff;
}


void populate_array(int *arr, int size, int rand_fd) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = generate_random(rand_fd);
    }
}


void write_to_file(int *buff) {
    int fd = open("nums.txt", O_WRONLY, 0);
    write(fd, buff, ARRAY_LEN * sizeof(*buff));
    if (errno) {
        printf("%s\n", strerror(errno));
    }
}


void read_file(int* buff) {
    int fd = open("nums.txt", O_RDONLY, 0);
    read(fd, buff, ARRAY_LEN * sizeof(*buff));
    if (errno) {
        printf("Error: %s\n", strerror(errno));
    }
}


int main() {

    int rand_fd = open("/dev/random", O_RDONLY, 0);
    if (rand_fd < 0) {
        printf("Error %s\n", strerror(errno));
    }

    int rand_nums[ARRAY_LEN];
    populate_array(rand_nums, ARRAY_LEN, rand_fd);

    printf("Generating random numbers:\n");
    int i;
    for (i = 0; i < ARRAY_LEN; i++) {
        printf("\trandom %d: %d\n", i, rand_nums[i]);
    }   


    printf("writing to file\n");
    write_to_file(rand_nums);

    printf("reading from file\n");
    int returned_rand_nums[ARRAY_LEN];
    read_file(returned_rand_nums);

    printf("verifying that result is correct:\n");
    for (i = 0; i < ARRAY_LEN; i++) {
        printf("\t random: %d: %d\n", i, returned_rand_nums[i]);
    }



    return 0;
}