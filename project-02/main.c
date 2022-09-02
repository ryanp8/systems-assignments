#include "editor.h"
#include "console.h"

#define EDIT 0
#define CONSOLE 1
#define CONSOLE_OUTPUT 2


static void sighandler(int signo) {
	if (signo == SIGINT) {
		endwin();
		exit(0);
	}
}


int main(int argc, char *argv[]) {

    if (argc > 1) {

		signal(SIGINT, sighandler);

		off_t fs = 1; // start at 1 so there's trailing 0;
		off_t console_len = 1;

		char *content = calloc(fs, sizeof(char));
		off_t console_input_len = 1;		
		char *console_input = calloc(console_input_len, sizeof(char));
		char *console_content = calloc(console_len, sizeof(char));

		int x = 0;
		int y = 0;

		int console_x = 0;
		int console_y = 0;

		int editor_max_x;
		int editor_max_y;

		int console_max_x;
		int console_max_y;

		int term_x = 0;
		int term_y = 0;

		int editor_top_row = 0;
		int console_top_row = 0;

		initscr();
		noecho();
		cbreak();
		getmaxyx(stdscr, term_y, term_x);

        WINDOW *editor = open_editor(argv[1], &fs, content, (int) (term_y * 0.7));
		getmaxyx(editor, editor_max_y, editor_max_x);
		if (fs > 1) {
			content = calloc(fs, sizeof(char));
			int fd = open(argv[1], O_RDONLY);
			read(fd, content, fs);
			draw_text(editor, content, 0, 0, fs);
		}
		draw_border(editor);
		draw_line_nums(editor, editor_max_y, editor_top_row);
		wrefresh(editor);

		WINDOW *console = open_console(editor_max_y);
		getmaxyx(console, console_max_y, console_max_x);
		mvwaddstr(console, 0, 0, ">>>");
		wrefresh(console);

		char *output = malloc(OUTPUT_LEN);
		off_t outplen = OUTPUT_LEN;
		WINDOW *console_output = open_output(editor_max_y + 1);
		int outx = 0;
		int outy = 0;
		int outtr = 0;
		int outmaxx, outmaxy;
		getmaxyx(console_output, outmaxy, outmaxx);

		int mode = EDIT;
		wmove(editor, y, x + WINDOW_X);

		int c;
		while (1) {
			// draw_border(console);
			if (mode == EDIT) {
				c = read_input(editor, &content, &mode, &fs, &x, &y, &editor_top_row, editor_max_x, editor_max_y);
				if (c == 27) {
					mode = CONSOLE;
				}
				draw_border(editor);
				draw_line_nums(editor, editor_max_y, editor_top_row);
				wmove(editor, y, x + WINDOW_X);
			}
			else if (mode == CONSOLE) {

				wmove(console, console_y, console_x + WINDOW_X);
				c = read_input(console, &console_input, &mode, &console_input_len, &console_x, &console_y, &console_top_row, console_max_x, console_max_y);

				if (c == 27) {
					mode = EDIT;
				}
				else if (c == '\n') {
					console_x = strlen(console_input) - 1;
					console_y = 0;
					free(output);
					output = calloc(OUTPUT_LEN, sizeof(char));
					console_input[console_input_len - 2] = 0;	
					console_input_len--;		
					if (run_command(console_input, output, content, argv[1], fs) != -1) {
						mode = CONSOLE_OUTPUT;
						console_x = strlen(console_input);
						console_y = 0;
					}

					outplen = strlen(output);
					draw_text(console_output, output, 0, 0, outplen);

					mvwaddstr(console, 0, 0, ">>>");
					// wrefresh(console);

					wmove(console_output, 0, WINDOW_X);
					wrefresh(console_output);
				}
				else {
					mvwaddstr(console, 0, 0, ">>>");
					wrefresh(console);
				}
			}
			else if (mode == CONSOLE_OUTPUT) {
				c = wgetch(console_output);
				handle_navigation(console_output, output, &outtr, c, &outx, &outy, outplen, outmaxy);
				switch(c) {
					case 27:
					case '\n':
						mode = EDIT;
						break;
					case KEY_F0:
					case KEY_BACKSPACE:
					case 127:
					case KEY_DL:
					case '\b':
						mode = CONSOLE;
				}
			}
		}

		endwin();	
		free(content);
    }

    return 0;
}
