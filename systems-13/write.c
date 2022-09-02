#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "write.h"
#include "print.h"
#include "entry.h"
#include "read.h"



void write_entry(struct pop_entry *entry) {
    int fd = open("nyc.data", O_WRONLY | O_APPEND);
    int res = write(fd, entry, sizeof(struct pop_entry));
    if (res == -1) {
        print_error();
        return;
    }
    close(fd);
}


int write_row(int row[6]) {
    char boros[5][15];
    strcpy(boros[0], "Manhattan");
    strcpy(boros[1], "Brooklyn");
    strcpy(boros[2], "Queens");
    strcpy(boros[3], "Bronx");
    strcpy(boros[4], "Staten Island");
    int bytes_written = 0;

    struct pop_entry entry;
    int j;
    for (j = 1; j < 6; j++) {
        entry.year = row[0];
        entry.population = row[j];
        strcpy(entry.boro, boros[j - 1]);
        write_entry(&entry);
        bytes_written += sizeof(struct pop_entry);
    }

    return bytes_written;
}


int write_data(char **rows, int nm) {
    int fd = open("nyc.data", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        print_error();
        return -1;
    }
    int bytes_written = 0;
    int i;
    for (i = 1; i < nm; i++) {
        int row[6];
        sscanf(rows[i], "%d,%d,%d,%d,%d,%d", row, row + 1, row + 2, row + 3, row + 4, row + 5);
        bytes_written += write_row(row);
    }
    close(fd);

    return bytes_written;
}


void add_data() {
    printf("Enter year boro pop: ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    struct pop_entry new_entry;
    sscanf(buffer, "%d %s %d\n", &(new_entry.year), new_entry.boro, &(new_entry.population));
    printf("appended data to file: year: %d\tboro: %s\t pop: %d\n", new_entry.year, new_entry.boro, new_entry.population);
    write_entry(&new_entry);
}


void update_data(struct pop_entry *current) {

    printf("entry to update: ");
    char entry_buffer[100];
    fgets(entry_buffer, sizeof(entry_buffer), stdin);
    int target_entry;
    sscanf(entry_buffer, "%d\n", &target_entry);

    printf("Enter year boro pop: ");
    char data_buffer[100];
    fgets(data_buffer, sizeof(data_buffer), stdin);
    struct pop_entry new_entry;
    sscanf(data_buffer, "%d %s %d", &(new_entry.year), new_entry.boro, &(new_entry.population));
    
    if (!data_buffer[0] || !entry_buffer[0]) {
        printf("Invalid entry\n");
        return;
    }
    
    strcpy(current[target_entry].boro, new_entry.boro);
    current[target_entry].population = new_entry.population;
    current[target_entry].year = new_entry.year;
    
    int ds = data_size();
    int fd = open("nyc.data", O_WRONLY | O_TRUNC);
    
    int res = write(fd, current, ds);
    if (res == -1) {
        print_error();
        return;
    }

    printf("File updated\n");
    close(fd);
}

