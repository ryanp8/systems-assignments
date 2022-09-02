#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "entry.h"
#include "read.h"
#include "write.h"
#include "print.h"



int main(int argc, char *argv[]) {

    if (argc > 1) {
        if (strcmp(argv[1], "-read_csv") == 0) {
            char **rows = read_csv();
            int nm = num_rows();
            int bytes_written = write_data(rows, nm);
            printf("wrote %d bytes to nyc.data\n", bytes_written);
        }
        if (strcmp(argv[1], "-read_data") == 0) {
            struct pop_entry *entries = read_data();
            print_entries(entries);
        }
        if (strcmp(argv[1], "-add_data") == 0) {
            add_data();
        }
        if (strcmp(argv[1], "-update_data") == 0) {
            struct pop_entry *current = read_data();
            print_entries(current);
            update_data(current);
        }
    }
    return 0;
}