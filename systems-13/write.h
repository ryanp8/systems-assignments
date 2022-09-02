#include "entry.h"
#ifndef WRITE_H
#define WRITE_H
void write_entry(struct pop_entry *entry);
int write_row(int row[6]);
int write_data(char **rows, int nm);
void add_data();
void update_data(struct pop_entry *current);
#endif