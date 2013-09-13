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

#endif
