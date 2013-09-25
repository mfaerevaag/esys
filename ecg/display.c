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

	move(0,0);

	refresh();
}

#endif
