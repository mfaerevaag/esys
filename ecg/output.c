#include "output.h"

#ifndef _OUTPUT_C_
#define _OUTPUT_C_

static FILE *output_file;

void init_output(char *output_file_name) {
	if (!opts.output_flag) return;

	output_file = fopen(output_file_name, "w");
	// write headers
	fprintf(output_file, "mwi,raw\n");
}

void destroy_output() {
	if (!opts.output_flag) return;

	fclose(output_file);
}

void update_output(float time, int mwi, int raw) {
	if (!opts.output_flag) return;

	fprintf(output_file, "%i,%i\n", mwi, raw);
}

#endif
