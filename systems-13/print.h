#ifndef PRINT_H
#define PRINT_H
#include "entry.h"
void print_entry(int idx, struct pop_entry *entry);
void print_entries(struct pop_entry *entries);
void print_error();
#endif