#include <stdlib.h>
#include <unistd.h>

#ifndef _OPT_PARSER_H_
#define _OPT_PARSER_H_

typedef struct options_s {
	char *file_name;
	int limit;
	char *output_file_name;
	int output_flag;
	int display_flag;
	float time_scale;
} options;

options parse_opts(int argc, char *argv[]);

#endif
