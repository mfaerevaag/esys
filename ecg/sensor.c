#include "sensor.h"

#ifndef _SENSOR_C_
#define _SENSOR_C_

static const char *filename = "ECG.txt";
static long fpos = 0;

int get_next_data() {
	FILE *file = fopen(filename, "r");
	
	fseek(file, fpos, SEEK_SET);

	int val;
	fscanf(file,"%i", &val);

	fpos = ftell(file);

	return val;
}

#endif
