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

//int unshift_array(int *arr, int arr_len) {
//	int ret = arr[0];
//	for (int i = 0; i < arr_len - 1; i++) {
//		arr[i] = arr[i + 1];
//	}
//	return ret;
//}
//
//int shift_array(int *arr, int arr_len) {
//	int ret = arr[arr_len - 1];
//	for (int i = arr_len - 1; i >= 0; i--) {
//		arr[i + 1] = arr[i];
//	}
//	// pad with 0
//	arr[0] = 0;
//
//	return ret;
//}

void prepend_array(int *arr, int arr_len, int val) {
	for (int i = arr_len - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
	arr[0] = val;
}

//void append_array(int *arr, int arr_len, int val) {     
//	unshift_array(arr, arr_len);
//	arr[arr_len - 1] = val;
//}

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
