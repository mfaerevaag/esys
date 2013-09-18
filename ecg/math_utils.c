#include "math_utils.h"

#ifndef _MATH_UTILS_C_
#define _MATH_UTILS_C_

int max_float(float a, float b) {
	return a > b ? a : b;
}

int max_int(int a, int b) {
	return a > b ? a : b;
}

int min_float(float a, float b) {
	return a < b ? a : b;
}

int min_int(int a, int b) {
	return a < b ? a : b;
}

#endif
