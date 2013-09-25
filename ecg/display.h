#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

void init_display();
void destroy_display();

void update_display(float time, int mwi, int rpk, int pk, float pulse);

#endif
