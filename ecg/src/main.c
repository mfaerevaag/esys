#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <ncurses.h>

#include "sensor.h"
#include "math_utils.h"
#include "filters.h"
#include "opt_parser.h"
#include "peak.h"
#include "peak_detect.h"
#include "array_utils.h"
#include "display.h"
#include "output.h"

options opts;

void int_handler(int sig);
void destroy();

int main(int argc, char *argv[]) {
	// register SIGNINT (ctrl-c) hook
	signal(SIGINT, int_handler);

	opts = parse_opts(argc, argv);

	init_output(opts.output_file_name);
	init_sensor(opts.file_name);
	init_filters();
	init_display();

	// it is given that sampling rate is 250 samples/sec
	float sample_rate = 1.0 / 250.0;

	int idx = 0;
	while (idx++ < opts.limit) {
		int data = get_next_data();
		int curr_size = min_int(idx, LIST_SIZE - 1) + 1;
		int *mwi = apply_all_filters(data, curr_size);
		
		peak_update pu = update_peak(mwi, idx);
		update_display(idx * sample_rate, mwi[1], data, pu);
		update_output(idx * sample_rate, mwi[1], data);
		
		if (pu.missed && 0)
			getchar();

		if (pu.found_r_peak && 0)
			printf("%i - %i - %i - MWI: %i - Count: %i\n", idx, pu.r_peak.value, pu.num_r_peaks, mwi[0], curr_size);
	}
	
	destroy();

	return 0;
}

void int_handler(int sig) {
	// exit gracefully
	signal(sig, SIG_IGN);
	destroy();
	exit(0);
}

void destroy() {
	destroy_output();
	destroy_sensor();
	destroy_display();
}
