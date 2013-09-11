#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sensor.h"
#include "filters.h"

int main() {
	init_sensor("test_data/ECG.txt");

	int max = 10000;
	int idx = 0;

	int sig[max], filt_low[max], filt_high[max], filt_der[max], filt_sqr[max], filt_win[max];
	do {
		sig[idx] = get_next_data();
		printf("%4i", sig[idx]);

		filt_low[idx] = apply_low_pass(sig, filt_low, idx + 1, idx);
		printf(" -> %8i", filt_low[idx]);

		filt_high[idx] = apply_high_pass(filt_low, filt_high, idx + 1, idx);
		printf(" -> %5i", filt_high[idx]);

		filt_der[idx] = apply_derivative(filt_high, filt_der, idx + 1, idx);
		printf(" -> %5i", filt_der[idx]);

		filt_sqr[idx] = apply_square(filt_der, filt_sqr, idx + 1, idx);
		printf(" -> %5i", filt_sqr[idx]);

		filt_win[idx] = apply_window(filt_sqr, filt_win, idx + 1, idx);
		printf(" -> %i\n", filt_win[idx]);
	} while (++idx < max);

	destroy_sensor();

	return 0;
}
