#include "opt_parser.h"

#ifndef _OPT_PARSER_C_
#define _OPT_PARSER_C_

options parse_opts(int argc, char *argv[]) {
	options opts2;
	
	opts2.file_name = "test_data/ECG.txt";
	opts2.output_file_name = "output/ecg_out.txt";
	opts2.output_flag = 0;
	opts2.limit = -1;
	opts2.display_flag = 0;
	opts2.time_scale = 1.0;

	char opt;
	while ((opt = getopt(argc, argv, "f:o:l:t:d")) != -1) {
		switch(opt) {
		case 'd':
			opts2.display_flag = 1;
			break;
		case 'f':
			opts2.file_name = optarg;
			break;
		case 'o':
			opts2.output_flag = 1;
			opts2.output_file_name = optarg;
			break;
		case 'l':
			opts2.limit = atoi(optarg);
			break;
		case 't':
			opts2.time_scale = atof(optarg);
			break;
		}
	}

	return opts2;
}

#endif
