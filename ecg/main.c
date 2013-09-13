#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "sensor.h"
#include "filters.h"
#include "opt_parser.h"
#include "array_utils.h"

// filter buffer size
static const int LIST_SIZE = 100000;

typedef int list[LIST_SIZE];

int main(int argc, char *argv[]) {
	struct options opts = parse_opts(argc, argv);
    
	init_sensor(opts.file_name);

	int idx, next_data;
	list sig, filt_low, filt_high, filt_der, filt_sqr, filt_win;
	while((next_data = get_next_data()) != 32767)  {
		// run filters
		sig[idx] = next_data;
		if (opts.print_flag) printf("%4i", sig[idx]);

		filt_low[idx] = apply_low_pass(sig, filt_low, idx + 1, idx);
		if (opts.print_flag) printf(" -> %8i", filt_low[idx]);

		filt_high[idx] = apply_high_pass(filt_low, filt_high, idx + 1, idx);
		if (opts.print_flag) printf(" -> %5i", filt_high[idx]);

		filt_der[idx] = apply_derivative(filt_high, filt_der, idx + 1, idx);
		if (opts.print_flag) printf(" -> %5i", filt_der[idx]);

		filt_sqr[idx] = apply_square(filt_der, filt_sqr, idx + 1, idx);
		if (opts.print_flag) printf(" -> %5i", filt_sqr[idx]);

		filt_win[idx] = apply_window(filt_sqr, filt_win, idx + 1, idx);
		if (opts.print_flag) printf(" -> %i\n", filt_win[idx]);

		idx++;
	}

	destroy_sensor();

	return 0;
}
