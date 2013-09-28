#include "sensor.h"

#ifndef _SENSOR_C_
#define _SENSOR_C_

static FILE *file;

void init_sensor(const char *filename) {
	file = fopen(filename, "r");
}

void destroy_sensor() {
	if (file != 0)
		fclose(file);
}

int get_next_data() {
	double sample_rate = 1.0 / 250.0;
	if (opts.time_scale > 0)
		usleep(sample_rate * 1000000.0 * (1 / opts.time_scale));

	int val;
	fscanf(file,"%i", &val);

	return val;
}

#endif
