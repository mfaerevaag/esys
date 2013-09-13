#include <stdlib.h>
#include <unistd.h>

#ifndef _OPT_PARSER_H_
#define _OPT_PARSER_H_

struct options {
	char *file_name;
	int print_flag;
};

struct options parse_opts(int argc, char *argv[]) {
	struct options opts;
	
	char *file_name = "test_data/ECG.txt";
	int print_flag = 0;

	char opt;
	while ((opt = getopt(argc, argv, "f:p")) != -1) {
		switch(opt) {
		case 'f':
			file_name = optarg;
			break;
		case 'p':
			print_flag = 1;
			break;
		}
	}

	opts.file_name = file_name;
	opts.print_flag = print_flag;

	return opts;
}

#endif
