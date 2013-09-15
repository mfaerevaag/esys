#include <stdlib.h>
#include <unistd.h>

#ifndef _OPT_PARSER_H_
#define _OPT_PARSER_H_

typedef struct options_s {
	char *file_name;
	int limit;
	int print_flag;
} options;

options parse_opts(int argc, char *argv[]) {
	options opts2;
	
	opts2.file_name = "test_data/ECG.txt";
	opts2.print_flag = 0;
	opts2.limit = -1;

	char opt;
	while ((opt = getopt(argc, argv, "f:pl:")) != -1) {
		switch(opt) {
		case 'f':
			opts2.file_name = optarg;
			break;
		case 'p':
			opts2.print_flag = 1;
			break;
		case 'l':
			opts2.limit = atoi(optarg);
			break;
		}
	}

	return opts2;
}

#endif
