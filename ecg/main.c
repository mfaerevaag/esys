#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"
#include "filters.h"

int main() {
	init_sensor("test_data/ECG.txt");

	int max = 40;
	int idx = 0;

	int sig[max], filt_low[max], filt_high[max];
	do {
		sig[idx] = get_next_data();
		printf("%4i", sig[idx]);

		filt_low[idx] = apply_low_pass(sig, filt_low, idx + 1, idx);
		printf(" -> %5i", filt_low[idx]);

		filt_high[idx] = apply_high_pass(filt_low, filt_high, idx + 1, idx);
		printf(" -> %5i\n", filt_high[idx]);
	} while (++idx < max);

	destroy_sensor();

	return 0;
}
