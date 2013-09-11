#include "filters.h"

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
	val_x -= sig_data[sig_len - 1] / 32.0;
    if (sig_len >= 17)
	val_x += sig_data[sig_len - 17];
    if (sig_len >= 18)
	val_x -= sig_data[sig_len - 18];
    if (sig_len >= 33)
	val_x += sig_data[sig_len - 33] / 32.0;

    return val_y + val_x;
}
