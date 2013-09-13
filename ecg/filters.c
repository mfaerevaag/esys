#include "filters.h"

#ifndef _FILTERS_C_
#define _FILTERS_C_

int apply_low_pass(int sig_data[], int filter_data[],
                   int sig_len, int filter_len) {

    int val_y = 0;
    if (filter_len >= 1)
        val_y += 2 * filter_data[filter_len - 1];
    if (filter_len >= 2)
        val_y -= filter_data[filter_len - 2];

    int val_x = 0;
    if (sig_len >= 1)
        val_x += sig_data[sig_len - 1];
    if (sig_len >= 7)
        val_x -= 2 * sig_data[sig_len - 7];
    if (sig_len >= 13)
        val_x += sig_data[sig_len - 13];

    val_x *= 1.0 / 32.0;

    return val_y + val_x;
}

int apply_high_pass(int sig_data[], int filter_data[],
                    int sig_len, int filter_len) {

    int val_y = 0;
    if (filter_len >= 1)
        val_y += filter_data[filter_len - 1];

    int val_x = 0;
    if (sig_len >= 1)
        val_x -= sig_data[sig_len - 1] / 32;
    if (sig_len >= 17)
        val_x += sig_data[sig_len - 17];
    if (sig_len >= 18)
        val_x -= sig_data[sig_len - 18];
    if (sig_len >= 33)
        val_x += sig_data[sig_len - 33] / 32;

    return val_y + val_x;
}

int apply_derivative(int sig_data[], int filter_data[], 
					 int sig_len, int filter_len) {
    int val_x = 0;
    if (sig_len >= 1)
        val_x += 2 * sig_data[sig_len - 1];
    if (sig_len >= 2)
        val_x += sig_data[sig_len - 2];
    if (sig_len >= 4)
        val_x -= sig_data[sig_len - 4];
    if (sig_len >= 5)
        val_x -= 2 * sig_data[sig_len - 5];

    val_x *= 1.0 / 8.0;

    return val_x;
}

int apply_square(int sig_data[], int filter_data[], 
				 int sig_len, int filter_len) {
    if (sig_len >= 1)
        return sig_data[sig_len - 1] * sig_data[sig_len - 1];
    return 0;
}

int apply_window(int sig_data[], int filter_data[], 
				 int sig_len, int filter_len) {
    int sum = 0;
    int count = sig_len < 31 ? sig_len : 31;

    for (int i = 1; i <= count; i++) {
	sum += sig_data[sig_len - i];
    }

    return sum / count;
}

#endif
