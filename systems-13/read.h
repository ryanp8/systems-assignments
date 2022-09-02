#ifndef READ_H
#define READ_H
char **read_csv();
char **split_rows(char *data, int file_size);
struct pop_entry *read_data();
int num_rows();
int data_size();
#endif