#include <stdlib.h>

#include "peak.h"

#ifndef _ARRAY_UTILS_H_
#define _ARRAY_UTILS_H_

// int
int unshift_array(int *arr, int arr_len);
int shift_array(int *arr, int arr_len);
void prepend_array(int *arr, int arr_len, int val);
void append_array(int *arr, int arr_len, int val);
float array_average_int(int *arr, int arr_len);

// float
void prepend_array_float(float *arr, int arr_len, float val);
void append_array_float(float *arr, int arr_len, float val);
float unshift_array_float(float *arr, int arr_len);
float array_average_float(float *arr, int arr_len);

// peak
void prepend_array_peak(peak *arr, int arr_len, peak val);
void append_array_peak(peak *arr, int arr_len, peak val);
peak unshift_array_peak(peak *arr, int arr_len);

#endif
