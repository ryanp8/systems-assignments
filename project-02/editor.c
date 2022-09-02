#include "editor.h"

WINDOW *open_editor(char *filename, off_t *fs, char *content, int height) {
    WINDOW *win = newwin(height, 0, 0, 0);
    keypad(win, TRUE);
    draw_line_nums(win, 2, 0);
    draw_border(win);
    wmove(win, WINDOW_Y, WINDOW_X);
    wrefresh(win);

    DIR *d;
    d = opendir(".");
    struct dirent *entry;
    while((entry = readdir(d))) {
        if (strcmp(entry->d_name, filename) == 0) {
            struct stat sb;
            stat(entry->d_name, &sb);
            *fs = sb.st_size + 1;
            break;
        }
    }
    closedir(d);

    return win;
}


void draw_border(WINDOW *win) {
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    int i;

    for (i = 0; i < max_x; i++) {
        mvwaddch(win, max_y - 1, i, ACS_HLINE);
    }
}


int handle_navigation(WINDOW *win, char *content, int *top_row, int c, int *x, int *y, int fs, int max_y) {
    char at_end;
    switch(c) {
        case KEY_UP:
            if (*y == 0 && *top_row > 0) {
                (*top_row)--;
                draw_text(win, content, char_instance(content, '\n', *top_row) + 1, *top_row, fs);
                wmove(win, WINDOW_Y, *x + WINDOW_X);
            }
            else if (*y > WINDOW_Y) {
                (*y)--;
                if (*x > line_len(content, *top_row + *y)) {
                    *x = line_len(content, *top_row + *y);
                }
                wmove(win, *y, *x + WINDOW_X);
            }
            return 0;
        case KEY_DOWN:
            at_end = (*top_row + *y >= strcount(content, '\n'));

            if (*y == max_y - 2 && !at_end) { // add 2 because max_y is border line
                (*top_row)++;
                draw_text(win, content, char_instance(content, '\n', *top_row) + 1, *top_row, fs);
            }
            else if (!at_end) {
                (*y)++;
                if (*x > line_len(content, *top_row + *y)) {
                    *x = line_len(content, *top_row + *y);
                }
                wmove(win, *y, *x + WINDOW_X);
            }
            return 0;
        case KEY_LEFT:
            if (*x > 0) {
                wmove(win, *y, --(*x) + WINDOW_X);
            }
            return 0;
        case KEY_RIGHT:
            if (*x < line_len(content, *top_row + *y)) {
                wmove(win, *y, ++(*x) + WINDOW_X);
            }
            return 0;
        default:
            return -1;
    }
}


char read_input(WINDOW *win, char **content_addr, int *mode, off_t *fs, int *x, int *y, int *top_row, int max_x, int max_y) {
    int c = wgetch(win);
    if (c == 27) {
        return c;
    }
    off_t pos;
    int space;

    char *content = *content_addr;

    if (handle_navigation(win, content, top_row, c, x, y, *fs, max_y) == -1) {
        switch(c) {
            case KEY_F0:
            case KEY_BACKSPACE:
            case 127:
            case '\b':
                pos = char_instance(content, '\n', *y + *top_row) + *x + 1;
                if (pos > 0) {
                    char deleted = content[pos - 1];
                    int prev_line_len = line_len(content, *y + *top_row - 1);
                    content[pos - 1] = 0;
                    off_t i;
                    for (i = pos - 1; i < *fs - 1; i++) {
                        char tmp = content[i];
                        content[i] = content[i + 1];
                        content[i + 1] = tmp;
                    }
                    (*fs)--;
                    draw_text(win, content, char_instance(content, '\n', *top_row) + 1, *top_row, *fs);
                    if (deleted == '\n') {
                        if (*y > 0) {
                            (*y)--;
                        }
                        else if (*top_row > 0) {
                            (*top_row)--;
                            draw_text(win, content, char_instance(content, '\n', *top_row) + 1, *top_row, *fs);
                        }
                        *x = prev_line_len;
                    }
                    else {
                        (*x)--;
                    }
                    wmove(win, *y, *x + WINDOW_X);
                    content_addr = realloc(content, *fs);
                }            
                break;
            case '\t':
            case KEY_STAB:
                for (space = 0; space < TAB_WIDTH; space++) {
                    add_char(content_addr, ' ', fs, *x, *top_row + *y);
                    draw_text(win, content, char_instance(content, '\n', *top_row) + 1, *top_row, *fs);
                    (*x)++;
                    wmove(win, *y, *x + WINDOW_X);
                }
                break;
            default:
                add_char(content_addr, c, fs, *x, *top_row + *y);
                draw_text(win, content, char_instance(content, '\n', *top_row) + 1, *top_row, *fs);
                if (c == '\n') {
                    *x = 0;
                    if (*y + 2 == max_y) { // max_y is the border line
                        (*top_row)++;
                        draw_text(win, content, char_instance(content, '\n', *top_row) + 1, *top_row, *fs);
                    }
                    else {
                        (*y)++;
                    }
                }
                else {
                    (*x)++;
                    // if (*x + WINDOW_X == max_x) {
                    //     *x = 0;
                    //     (*y)++;
                    // }
                }
                wmove(win, *y, *x + WINDOW_X);
        }
    
    }
    wrefresh(win);

    return c;
}


void draw_text(WINDOW *win, char *content, int start_pos, int top_row, off_t fs) {
    wclear(win);
    int x = 0;
    int y = 0;
    int max_x = getmaxx(win);
    int i;
    for (i = start_pos; i < fs - 1; i++) { // fs - 1 to exclude trailing 0
        mvwaddch(win, y, x + WINDOW_X, content[i]);
        if (content[i] == '\n') {
            x = 0;
            y++;
        }
        else {
            x++;
            // if (x + WINDOW_X == max_x) {
            //     x = 0;
            //     y++;
            // }
        }
    }
    // wprintw(win, content);  
}


void add_char(char **content, char c, off_t *fs, int x, int y) {
    (*fs)++;
    content[0] = realloc(content[0], *fs);
    off_t pos = char_instance(content[0], '\n', y) + x + 1; // current position of cursor in relation to raw text

    off_t i;
    for (i = *fs - 1; i > pos; i--) {
        char tmp = content[0][i];
        content[0][i] = content[0][i - 1];
        content[0][i - 1] = tmp;
    }
    content[0][pos] = (char) c; 
}


void draw_line_nums(WINDOW *win, int height, int top_row) {
    int i;
    for (i = 0; i < height - 1; i++) {
        mvwprintw(win, i, 0, "%d", top_row + i + 1);
    }
}



off_t char_instance(char *str, char c, off_t n) {
    off_t counter = 0;
    off_t i = 0;
    while (i < strlen(str)) {
        if (str[i] == c) {
            counter++;
            if (counter == n) return i;
        }
        i++;
    }
    return -1;
}

int line_len(char *content, int y) {
    y++;
    if (y == 1) {
        int f = (int) char_instance(content, '\n', 1);
        if (f == -1) {
            return strlen(content);
        }
        return f;
    }
    int first = (int) char_instance(content, '\n', y - 1);
    int second = (int) char_instance(content, '\n', y);
    if (second == -1) {
        return strlen(content + first) - 1;
    }
    return second - first - 1;
}

int strcount(char *str, char c) {
    int count = 0;
    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
    return count;
}