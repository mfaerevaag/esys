#include "display.h"

#ifndef _DISPLAY_C_
#define _DISPLAY_C_


void init_display() {
	if (!opts.display_flag) return;

	initscr();
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	init_pair(4, COLOR_RED, COLOR_BLUE);
}

void destroy_display() {
	if (!opts.display_flag) return;

	attron(COLOR_PAIR(1));
	mvhline(W_SIZE.y / 2, 0, ' ', W_SIZE.x);
	mvprintw(W_SIZE.y / 2, W_SIZE.x / 2 - 10, "PRESS ANY KEY TO EXIT");
	attroff(COLOR_PAIR(1));

	getch();
	endwin();
}

void update_display(float time, int mwi, int raw, peak_update pu) {
	if (!opts.display_flag) return;

	// add mwi to local buffer
	prepend_array_int(raw_buffer, GRAPH_WIDTH, raw);

	// update terminal size
	struct winsize term_w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &term_w);
	W_SIZE.x = term_w.ws_col;

	// clear screen
	erase();

	// labels
	mvprintw(OFFSET.y, OFFSET.x, "Time:");
	mvprintw(OFFSET.y + 1, OFFSET.x, "MWI:");
	mvprintw(OFFSET.y + 2, OFFSET.x, "Last R-peak:");
	mvprintw(OFFSET.y + 3, OFFSET.x, "Last peak:");
	mvprintw(OFFSET.y + 4, OFFSET.x, "BPM:");
	mvprintw(OFFSET.y + 5, OFFSET.x, "# R-peaks:");
	mvprintw(OFFSET.y + 6, OFFSET.x, "Misses:");

	// values
	int col = COL_WIDTH - 4;

	mvprintw(OFFSET.y, col, "%5.2f", time);
	mvprintw(OFFSET.y + 1, col, "%5i", mwi);

	if (pu.r_peak.value < 2000 && pu.r_peak.value != 0)
		attron(COLOR_PAIR(1));

	mvprintw(OFFSET.y + 2, col, "%5i", pu.r_peak.value);

	if (pu.r_peak.value < 2000 && pu.r_peak.value != 0)
		attroff(COLOR_PAIR(1));

	mvprintw(OFFSET.y + 3, col, "%5i", pu.n_peak.value);
	float bpm = (60.0 * 250) / pu.pulse;
	mvprintw(OFFSET.y + 4, col, "%5.1f", bpm);
	mvprintw(OFFSET.y + 5, col, "%5i", pu.num_r_peaks);

	if (pu.consec_missed > 4)
		attron(COLOR_PAIR(1));

	mvprintw(OFFSET.y + 6, col, "%5i", pu.consec_missed);

	if (pu.consec_missed > 4)
		attroff(COLOR_PAIR(1));

	// graph
	int flatline = W_SIZE.y / 1.5;
	int graph_len = W_SIZE.x - 3 * OFFSET.x - COL_WIDTH > GRAPH_WIDTH ? GRAPH_WIDTH : W_SIZE.x - 3 * OFFSET.x - COL_WIDTH;

	mvhline(flatline, COL_WIDTH + 2 * OFFSET.x, '_', graph_len);

	attron(COLOR_PAIR(2));
	int last = 0;
	for (int i = 0; i < graph_len; i++) {
		int curr = raw_buffer[i] / 50.0;
		char ch = curr > last ? '\\' : (curr < last ? '/' : '_');
		int real_curr = ch == '\\' ? curr : curr + 1;

		mvaddch(flatline + 1 - real_curr, graph_len + 2 * OFFSET.x + COL_WIDTH - i - 1, ch);

		last = curr;
	}
	attroff(COLOR_PAIR(2));

	// outline
	attron(COLOR_PAIR(3));
	mvhline(0, 0, ' ', W_SIZE.x); // top horizontal
	mvhline(W_SIZE.y, 0, ' ', W_SIZE.x); // bottom horizontal
	mvvline(0, 0, ' ', W_SIZE.y); // left vertical
	mvvline(0, W_SIZE.x - 1, ' ', W_SIZE.y); // right vertical

	mvvline(0, COL_WIDTH + OFFSET.x, ' ', W_SIZE.y); // right vertical

	attroff(COLOR_PAIR(3));


	// title
	attron(A_BOLD | COLOR_PAIR(3));
	mvprintw(0, W_SIZE.x / 2 - 6, "Medembed ECG");
    attroff(A_BOLD | COLOR_PAIR(3));

	move(0, 0);
	refresh();
}

#endif
