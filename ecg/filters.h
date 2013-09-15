#include <stdlib.h>
#include <math.h>

#ifndef _FILTERS_H_
#define _FILTERS_H_

int apply_low_pass(int sig_data[], int filter_data[]);

int apply_high_pass(int sig_data[], int filter_data[]);

int apply_derivative(int sig_data[], int filter_data[]);

int apply_square(int sig_data[], int filter_data[]);

int apply_window(int sig_data[], int filter_data[]);

#endif
