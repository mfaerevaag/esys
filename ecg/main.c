#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>

#include "sensor.h"
#include "filters.h"
#include "opt_parser.h"
#include "peak_detect.h"
#include "array_utils.h"
#include "display.h"
#include "output.h"

options opts;

int main(int argc, char *argv[]) {
	opts = parse_opts(argc, argv);

	init_output(opts.output_file_name);
	init_sensor(opts.file_name);
	init_filters();
	init_display();

	int idx = 0;
	double time = 0;
	// it is given that sampling rate is 250 samples/sec
	double sample_rate = 1.0 / 250.0;

	while (idx < opts.limit) {
		usleep(sample_rate * 1000000.0);
		time += sample_rate;
		int data = get_next_data();
        int curr_size = (idx < LIST_SIZE - 1 ? idx : LIST_SIZE - 1) + 1;
		int *mwi = apply_all_filters(data, curr_size);

		float pulse;
		peak rpeak;
		peak npeak;

		update_peak(mwi, idx, &pulse, &rpeak, &npeak);
		update_display(time, mwi[0], rpeak.value, npeak.value, pulse, data);
		update_output(time, mwi[0], data);

		idx++;
	}
	
	destroy_output();
	destroy_sensor();
	destroy_display();

	return 0;
}
