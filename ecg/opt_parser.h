#include <stdlib.h>
#include <unistd.h>

#ifndef _OPT_PARSER_H_
#define _OPT_PARSER_H_

typedef struct options_s {
	char *file_name;
	int limit;
	int print_flag;
} options;

options parse_opts(int argc, char *argv[]);

#endif
