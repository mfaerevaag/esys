#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"
#include "filters.h"

int main() {
	init_sensor("test_data/ECG.txt");

	int max = 10000;
	int idx = 0;

	int filt[max];
	int sig[max];
	do {
		sig[idx] = get_next_data();
		filt[idx] = apply_low_pass(sig, filt, idx + 1, idx);

		printf("%i \t\t-> %i\n", sig[idx], filt[idx]);
	} while (++idx < max);

	destroy_sensor();

	return 0;
}
