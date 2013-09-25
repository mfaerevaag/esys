#include "display.h"

#ifndef _DISPLAY_C_
#define _DISPLAY_C_


void init_display() {
	initscr();
}

void destroy_display() {
	endwin();
}

void update_display(float time, int mwi, int rpk, int pk, float pulse) {	
	// add mwi to local buffer
	prepend_array_int(mwi_buffer, 100, mwi);

	// clear screen
	erase();
	
	// labels
	mvprintw(1, 1, "Time:");
	mvprintw(2, 1, "MWI:");	
	mvprintw(3, 1, "Last R-peak:");	
	mvprintw(4, 1, "Last peak:");	
	mvprintw(5, 1, "Pulse:");

	// values
	mvprintw(1, 15, "%5.2f", time);
	mvprintw(2, 15, "%5i", mwi);	
	mvprintw(3, 15, "%5i", rpk);	
	mvprintw(4, 15, "%5i", pk);	
	mvprintw(5, 15, "%5.1f", pulse);

	// graph
	int y_max = 1000;
	//int y_min = -100;
	// top right bottom left
	int box[4] = {1, 400, 30, 20};
	int xs = 100;
	for (int i = 0; i < xs; i++) {
		mvaddch(box[0] + box[2] - (mwi_buffer[i] / 200.0), box[3] + i, '*');
	}

	move(0,0);

	refresh();
}

#endif
