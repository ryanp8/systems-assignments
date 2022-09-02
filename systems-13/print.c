#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "print.h"
#include "entry.h"
#include "read.h"

void print_error() {
    printf("Error %d: %s\n", errno, strerror(errno));
}

void print_entry(int idx, struct pop_entry *entry) {
    printf("%d: { boro: %s, year: %d, population: %d }\n", idx, entry->boro, entry->year, entry->population);
}


void print_entries(struct pop_entry *entries) {
    int ds = data_size();
    int id = 0;
    while (id < ds / sizeof(struct pop_entry)) {
        printf("%d: { boro: %s, year: %d, population: %d }\n", id, entries[id].boro, entries[id].year, entries[id].population);
        id++;    
    }
}