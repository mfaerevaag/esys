#include <stdlib.h>
#include <stdio.h>

#include "array_utils.h"
#include "math_utils.h"
#include "peak.h"

#ifndef _PEAK_DETECT_H_
#define _PEAK_DETECT_H_
#define PEAK_BUFFER_SIZE 8
#define PEAK_BUFFER_SIZE2 100

// vars
static float threshold1;
static float threshold2;
static float rr_average1;
static float rr_average2;
static float rr_low = 0;
static float rr_high = 10000000;
static float rr_miss;
static float spkf;
static float npkf;

static peak peaks[PEAK_BUFFER_SIZE2];
static peak r_peaks[PEAK_BUFFER_SIZE];

static float rr[PEAK_BUFFER_SIZE];
static float rr_ok[PEAK_BUFFER_SIZE];

static float rr_count = 0;
static float rr_ok_count = 0;

int update_peak(int *mwi, int time, float *pulseOut, peak *r_peak);

#endif
