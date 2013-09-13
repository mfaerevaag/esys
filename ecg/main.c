#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "sensor.h"
#include "filters.h"

int main(int argc, char *argv[]) {
	// arg parsing
    char *file_name = "test_data/ECG.txt";
	int print_flag = 0;

	char opt;
	while ((opt = getopt(argc, argv, "f:p")) != -1) {
		switch(opt) {
		case 'f':
			file_name = optarg;
			break;
		case 'p':
			print_flag = 1;
			break;
		}
	}

	init_sensor(file_name);

	int max = 10000;
	int idx = 0;

	int sig[max], filt_low[max], filt_high[max], filt_der[max], filt_sqr[max], filt_win[max];
	do {
		sig[idx] = get_next_data();
		if (print_flag) printf("%4i", sig[idx]);

		filt_low[idx] = apply_low_pass(sig, filt_low, idx + 1, idx);
		if (print_flag) printf(" -> %8i", filt_low[idx]);

		filt_high[idx] = apply_high_pass(filt_low, filt_high, idx + 1, idx);
		if (print_flag) printf(" -> %5i", filt_high[idx]);

		filt_der[idx] = apply_derivative(filt_high, filt_der, idx + 1, idx);
		if (print_flag) printf(" -> %5i", filt_der[idx]);

		filt_sqr[idx] = apply_square(filt_der, filt_sqr, idx + 1, idx);
		if (print_flag) printf(" -> %5i", filt_sqr[idx]);

		filt_win[idx] = apply_window(filt_sqr, filt_win, idx + 1, idx);
		if (print_flag) printf(" -> %i\n", filt_win[idx]);
	} while (++idx < max);

	destroy_sensor();

	return 0;
}
