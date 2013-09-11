#include "sensor.h"

#ifndef _SENSOR_C_
#define _SENSOR_C_

static long fpos = 0;
static FILE *file;

void init_sensor(const char *filename) {
	file = fopen(filename, "r");
}

void destroy_sensor() {
	if (file != 0)
		fclose(file);
}

int get_next_data() {
	
	fseek(file, fpos, SEEK_SET);

	int val;
	fscanf(file,"%i", &val);

	fpos = ftell(file);

	return val;
}


#endif
