#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "sensor.h"
#include "filters.h"
#include "opt_parser.h"
#include "peak_detect.h"
#include "array_utils.h"

options opts;

int main(int argc, char *argv[]) {
	opts = parse_opts(argc, argv);
    
	if (opts.print_flag) printf("Medembed ECG monitor\n");

	init_sensor(opts.file_name);
	init_filters();

	int idx = 0;
	double time = 0;
	// it is given that sampling rate is 250 samples/sec
	double sample_rate = 1.0 / 250.0;

	while (idx < opts.limit) {
		usleep(sample_rate * 1000000.0);
		time += sample_rate;

        int curr_size = (idx < LIST_SIZE - 1 ? idx : LIST_SIZE - 1) + 1;
		int *mwi = apply_all_filters(get_next_data(), curr_size);

		float pulse;
		peak rpeak;
		peak npeak;
		if (opts.print_flag)  {
			update_peak(mwi, idx, &pulse, &rpeak, &npeak);
			peak pk = rpeak;
			peak npk = npeak;

			printf(" R-Peak: %5i, N-Peak: %5i, Time: %05.2f, Pulse: %4.2f, Avg: %5i",
				   pk.value, npk.value, time, pulse, mwi[0]);

			if (pk.value < 2000) 
				printf(" Warning: Peak < 2000: %5i ", pk.value);
			else
				printf("                                        ", pk.value);

			printf("\r");
			fflush(stdout);
		}
		
		idx++;
	}


	if (opts.print_flag) printf("\n");

	destroy_sensor();

	return 0;
}
