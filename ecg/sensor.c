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
	int val;
	fscanf(file,"%i", &val);

	return val;
}

#endif
