#include <stdio.h>
#include <stdlib.h>

#include "opt_parser.h"

#ifndef _SENSOR_H_
#define _SENSOR_H_

extern options opts;

void init_sensor();
void destroy_sensor();
int get_next_data();

#endif
