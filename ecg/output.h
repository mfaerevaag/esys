#include <stdlib.h>
#include <stdio.h>

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

void init_output(char *output_file_name);
void destroy_output();

void update_output(float time, int mwi, int raw);

#endif
