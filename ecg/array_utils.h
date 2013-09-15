#include <stdlib.h>

#ifndef _ARRAY_UTILS_H_
#define _ARRAY_UTILS_H_

int unshift_array(int *arr, int arr_len) {
	int ret = arr[0];
	for (int i = 0; i < arr_len - 1; i++) {
		arr[i] = arr[i + 1];
	}
	return ret;
}

int shift_array(int *arr, int arr_len) {
	int ret = arr[arr_len - 1];
	for (int i = arr_len - 1; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
	// pad with 0
	arr[0] = 0;

	return ret;
}

void prepend_array(int *arr, int arr_len, int val) {
	for (int i = arr_len - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
	arr[0] = val;
}

void append_array(int *arr, int arr_len, int val) {     
	unshift_array(arr, arr_len);
	arr[arr_len - 1] = val;
}

#endif
