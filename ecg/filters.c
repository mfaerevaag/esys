#include "filters.h"

#ifndef _FILTERS_C_
#define _FILTERS_C_

static list sig, filt_low, filt_high, filt_der, filt_sqr, filt_win;

void init_filters() {
	for (int i = 0; i < LIST_SIZE; i++) {
		// TODO this might not be needed because the lists are declared static
		sig[i] = filt_high[i] = filt_low[i] = filt_der[i] = filt_sqr[i] = filt_win[i] = 0;
	}
}

int *apply_all_filters(int data, int curr_size) {
	prepend_array_int(sig, curr_size, data);
	prepend_array_int(filt_low, curr_size, apply_low_pass(sig, filt_low));
	prepend_array_int(filt_high, curr_size, apply_high_pass(filt_low, filt_high));
	prepend_array_int(filt_der, curr_size, apply_derivative(filt_high, filt_der));
	prepend_array_int(filt_sqr, curr_size, apply_square(filt_der, filt_sqr));
	prepend_array_int(filt_win, curr_size, apply_mwi(filt_sqr, filt_win));

	return filt_win;
}

/// respective filters
// sd = signal data, fd = filtered data
// the sd list is updated before filters are applied 
// which means that sd[0] = Xn, whereas fd[0] = Yn-1 
static int apply_low_pass(int sd[], int fd[]) {
    int val_y = (2 * fd[0]) - fd[1];
    int val_x = (sd[0] - (2 * sd[6]) + sd[12]) / 32;
	    
    return val_y + val_x;
}

static int apply_high_pass(int sd[], int fd[]) {
    int val_y = fd[0];
    int val_x = -(sd[0] / 32) + sd[16] - sd[17] + (sd[32] / 32);
	
    return val_y + val_x;
}

static int apply_derivative(int sd[], int fd[]) {
    int val_x = (2 * sd[0]) + sd[1] - sd[3] - (2 * sd[4]);
	val_x /= 8;

    return val_x;
}

static int apply_square(int sd[], int fd[]) {
	return sd[0] * sd[0];
}

static int apply_mwi(int sd[], int fd[]) {
    int sum = 0;
    for (int i = 1; i < 30; i++) {
		sum += sd[i] / 30.0;
    }
    return sum;
}

#endif
