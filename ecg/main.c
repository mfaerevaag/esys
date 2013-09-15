#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "sensor.h"
#include "filters.h"
#include "opt_parser.h"
#include "array_utils.h"

// filter buffer size
static const int LIST_SIZE = 33;
static options opts;
typedef int list[LIST_SIZE];

int main(int argc, char *argv[]) {
	opts = parse_opts(argc, argv);
    
	init_sensor(opts.file_name);

	int idx;
	list sig, filt_low, filt_high, filt_der, filt_sqr, filt_win;

	// zero-init lists
	for (int i = 0; i < LIST_SIZE; i++) {
		sig[i] = filt_high[i] = filt_low[i] = filt_der[i] = filt_sqr[i] = filt_win[i] = 0;
	}

	while(idx < opts.limit)  {
        int curr_size = (idx < LIST_SIZE - 1 ? idx : LIST_SIZE - 1) + 1;
        int sig_data = get_next_data();

        prepend_array(sig, curr_size, sig_data);
		if (opts.print_flag) printf("%4i", sig[0]);

		prepend_array(filt_low, curr_size, apply_low_pass(sig, filt_low));
		if (opts.print_flag) printf(" -> %8i", filt_low[0]);

		prepend_array(filt_high, curr_size, apply_high_pass(filt_low, filt_high));
		if (opts.print_flag) printf(" -> %5i", filt_high[0]);

		prepend_array(filt_der, curr_size, apply_derivative(filt_high, filt_der));
		if (opts.print_flag) printf(" -> %5i", filt_der[0]);

		prepend_array(filt_sqr, curr_size, apply_square(filt_der, filt_sqr));
		if (opts.print_flag) printf(" -> %5i", filt_sqr[0]);

		prepend_array(filt_win, curr_size, apply_window(filt_sqr, filt_win));
		if (opts.print_flag) printf(" -> %i\n", filt_win[0]);

		idx++;
	}

	destroy_sensor();

	return 0;
}
