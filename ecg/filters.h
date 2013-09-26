#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "opt_parser.h"
#include "array_utils.h"

#ifndef _FILTERS_H_
#define _FILTERS_H_

#define LIST_SIZE 33

typedef int list[LIST_SIZE];
extern options opts;

static int apply_low_pass(int sig_data[], int filter_data[]);
static int apply_high_pass(int sig_data[], int filter_data[]);
static int apply_derivative(int sig_data[], int filter_data[]);
static int apply_square(int sig_data[], int filter_data[]);
static int apply_mwi(int sig_data[], int filter_data[]);

int *apply_all_filters(int data, int curr_size);
void init_filters();

#endif
