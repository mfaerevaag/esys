#include "output.h"

#ifndef _OUTPUT_C_
#define _OUTPUT_C_

static FILE *output_file;

void init_output(char *output_file_name) {
	output_file = fopen(output_file_name, "w");
	// write headers
	fprintf(output_file, "mwi,raw\n");
}

void destroy_output() {
	fclose(output_file);
}

void update_output(float time, int mwi, int raw) {
	fprintf(output_file, "%i,%i\n", mwi, raw);
}

#endif
