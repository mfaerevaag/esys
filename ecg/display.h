#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "array_utils.h"
#include "peak.h"

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

static int raw_buffer[100];

void init_display();
void destroy_display();

void update_display(float time, int mwi, int raw, peak_update pu);

#endif
