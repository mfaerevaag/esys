#include "display.h"

#ifndef _DISPLAY_C_
#define _DISPLAY_C_

void init_display() {
	initscr();
    start_color();

    //init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

void destroy_display() {
	endwin();
}

void update_display(float time, int mwi, int rpk, int pk, float pulse, int raw) {	
	// add mwi to local buffer
	prepend_array_int(raw_buffer, 100, raw);

	// clear screen
	erase();
	
	// title
    attron(COLOR_PAIR(3));
	mvprintw(0, 0, "                      \n Medembed ECG monitor \n                      ");
    attroff(COLOR_PAIR(3));

	int y_base = 3;

	// labels
	mvprintw(y_base + 1, 1, "Time:");
	mvprintw(y_base + 2, 1, "MWI:");	
	mvprintw(y_base + 3, 1, "Last R-peak:");	
	mvprintw(y_base + 4, 1, "Last peak:");	
	mvprintw(y_base + 5, 1, "Pulse:");

	// values
	mvprintw(y_base + 1, 15, "%5.2f", time);
	mvprintw(y_base + 2, 15, "%5i", mwi);	
	mvprintw(y_base + 3, 15, "%5i", rpk);	
	mvprintw(y_base + 4, 15, "%5i", pk);	
	mvprintw(y_base + 5, 15, "%5.1f", pulse);

	// graph
    attron(COLOR_PAIR(2));
	// top right bottom left
	int xs = 100;
	int box[4] = {1, xs, 20, 20};
	for (int i = 0; i < xs; i++) {
		mvaddch(y_base + box[0] + box[2] - (raw_buffer[i] / 50.0), box[3] + box[1] - i, '*');
	}
	attroff(COLOR_PAIR(2));
	
	// warn if R-peak is less than 2k
	if (rpk < 2000 && rpk != 0) {
		attron(COLOR_PAIR(1));
		mvprintw(y_base + 7, 1, "WARNING!");
		attroff(COLOR_PAIR(1));
		mvprintw(y_base + 8, 1, "Weak beat");
	}

	move(0, 0);

	refresh();
}

#endif
