#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "array_utils.h"
#include "opt_parser.h"
#include "peak.h"

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

extern options opts;

typedef struct dimension_s {
		int x;
		int y;
} dimension;

static dimension W_SIZE = { .y = 33 };
static dimension OFFSET = { 2, 2 };
static int COL_WIDTH = 20;

#define GRAPH_WIDTH 100

static int raw_buffer[GRAPH_WIDTH];

void init_display();
void destroy_display();

void update_display(float time, int mwi, int raw, peak_update pu);

#endif
