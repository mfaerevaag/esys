#include "array_utils.h"

#ifndef _ARRAY_UTILS_C_
#define _ARRAY_UTILS_C_

// int
float array_average_int(int *arr, int arr_len) {
	float sum = 0.0;
	for (int i = 0; i < arr_len; i++) {
		sum += arr[i];
	}

	return sum / arr_len;
}

void prepend_array_int(int *arr, int arr_len, int val) {
	for (int i = arr_len - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
	arr[0] = val;
}

// peaks
void prepend_array_peak(peak *arr, int arr_len, peak val) {
	for (int i = arr_len - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
	arr[0] = val;
}

// float
void prepend_array_float(float *arr, int arr_len, float val) {     
	for (int i = arr_len - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
	arr[0] = val;
}

float array_average_float(float *arr, int arr_len) {
	float sum = 0.0;
	for (int i = 0; i < arr_len; i++) {
		sum += arr[i];
	}

	return sum / arr_len;
}

#endif
