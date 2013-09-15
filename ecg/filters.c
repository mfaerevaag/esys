#include "filters.h"

#ifndef _FILTERS_C_
#define _FILTERS_C_

// sd = signal data
// fd = filtered data

// the sd list is updated before filters are applied 
// which means that sd[0] = Xn, whereas fd[0] = Yn-1 

int apply_low_pass(int sd[], int fd[]) {
    int val_y = (2 * fd[0]) - fd[1];
    int val_x = (sd[0] - (2 * sd[6]) + sd[12]) / 32;
	    
    return val_y + val_x;
}

int apply_high_pass(int sd[], int fd[]) {
    int val_y = fd[0];
    int val_x = -(sd[0] / 32) + sd[16] - sd[17] + (sd[32] / 32);
	
    return val_y + val_x;
}

int apply_derivative(int sd[], int fd[]) {
    int val_x = (2 * sd[0]) + sd[1] - sd[3] - (2 * sd[4]);
	val_x /= 8;

    return val_x;
}

int apply_square(int sd[], int fd[]) {
	return sd[0] * sd[0];
}

int apply_window(int sd[], int fd[]) {
    int sum = 0;

    for (int i = 1; i < 30; i++) {
		sum += sd[i];
    }

    return sum / 30;
}

#endif
