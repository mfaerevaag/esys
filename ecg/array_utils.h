#include <stdlib.h>

#ifndef _ARRAY_UTILS_H_
#define _ARRAY_UTILS_H_

int unshift_array(int *arr, int arr_len);
int shift_array(int *arr, int arr_len);

void prepend_array(int *arr, int arr_len, int val);
void append_array(int *arr, int arr_len, int val);

#endif
