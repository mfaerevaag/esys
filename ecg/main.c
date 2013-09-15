#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "sensor.h"
#include "filters.h"
#include "opt_parser.h"

options opts;

int main(int argc, char *argv[]) {
	opts = parse_opts(argc, argv);
    
	init_sensor(opts.file_name);
	init_filters();

	int idx = 0;
	
	while(idx < opts.limit)  {
        int curr_size = (idx < LIST_SIZE - 1 ? idx : LIST_SIZE - 1) + 1;

        int data = get_next_data();
		
		int *mwi = apply_all_filters(data, curr_size);

		if (opts.print_flag) printf("%4i\n", mwi[0]);
		
		idx++;
	}

	destroy_sensor();

	return 0;
}
