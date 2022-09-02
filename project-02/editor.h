#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ncurses.h>

#ifndef EDITOR_H
#define EDITOR_H

#define WINDOW_X 4
#define WINDOW_Y 0
#define TAB_WIDTH 4

WINDOW *open_editor(char *filename, off_t *fs, char *content, int height);
void draw_border(WINDOW *win);
int handle_navigation(WINDOW *win, char *content, int *top_row, int c, int *x, int *y, int fs, int max_y);
char read_input(WINDOW *win, char **content_addr, int *mode, off_t *fs, int *x, int *y, int* top_row, int max_x, int max_y);
void add_char(char **content, char c, off_t *fs, int x, int y);
void draw_text(WINDOW *win, char *content, int start_pos, int top_row, off_t fs);
void draw_line_nums(WINDOW *win, int height, int top_row);
int line_len(char *content, int y);
int strcount(char *content, char c);
off_t char_instance(char *str, char c, off_t n);



#endif