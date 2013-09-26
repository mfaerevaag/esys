#include "display.h"

#ifndef _DISPLAY_C_
#define _DISPLAY_C_

void init_display() {
	if (!opts.display_flag) return;

	initscr();
    start_color();

    //init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
}

void destroy_display() {
	if (!opts.display_flag) return;

	endwin();
}

void update_display(float time, int mwi, int raw, peak_update pu) {	
	if (!opts.display_flag) return;

	// add mwi to local buffer
	prepend_array_int(raw_buffer, 100, raw);

	// clear screen
	erase();
	
	// title
    attron(COLOR_PAIR(3));
	mvprintw(2, 0, "     Medembed ECG %i    ", opts.display_flag);
    attroff(COLOR_PAIR(3));

	int y_base = 3;

	// labels
	mvprintw(y_base + 1, 1, "Time:");
	mvprintw(y_base + 2, 1, "MWI:");	
	mvprintw(y_base + 3, 1, "Last R-peak:");	
	mvprintw(y_base + 4, 1, "Last peak:");	
	mvprintw(y_base + 5, 1, "Pulse:");
	mvprintw(y_base + 6, 1, "# R-peaks:");
	mvprintw(y_base + 7, 1, "Misses:");

	// values
	mvprintw(y_base + 1, 15, "%5.2f", time);
	mvprintw(y_base + 2, 15, "%5i", mwi);	

	if (pu.r_peak.value < 2000 && pu.r_peak.value != 0) 
		attron(COLOR_PAIR(1));

	mvprintw(y_base + 3, 15, "%5i", pu.r_peak.value);	

	if (pu.r_peak.value < 2000 && pu.r_peak.value != 0) 
		attroff(COLOR_PAIR(1));

	mvprintw(y_base + 4, 15, "%5i", pu.n_peak.value);	
	mvprintw(y_base + 5, 15, "%5.1f", pu.pulse);
	mvprintw(y_base + 6, 15, "%5i", pu.num_r_peaks);

	if (pu.conseq_missed > 4) 
		attron(COLOR_PAIR(1));

	mvprintw(y_base + 7, 15, "%5i", pu.conseq_missed);

	if (pu.conseq_missed > 4) 
		attroff(COLOR_PAIR(1));

	mvhline(y_base, 0, '-', 21);
	
	// graph
    attron(COLOR_PAIR(2));
	// top right bottom left
	int xs = 100;
	int box[4] = {1, xs, 20, 20};
	int last = 0;
	for (int i = 0; i < xs; i++) {
		int curr = raw_buffer[i];
		char ch = curr > last ? '/' : (curr < last ? '\\' : '-');
		mvaddch(y_base + box[0] + box[2] - (curr / 50.0), box[3] + box[1] - i, ch);
	}
	attroff(COLOR_PAIR(2));

	move(0, 0);

	refresh();
}

#endif
