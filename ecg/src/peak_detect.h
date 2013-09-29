#include <stdlib.h>
#include <stdio.h>

#include "array_utils.h"
#include "math_utils.h"
#include "peak.h"

#ifndef _PEAK_DETECT_H_
#define _PEAK_DETECT_H_
#define R_PEAK_BUFFER_SIZE 8
#define PEAK_BUFFER_SIZE 5

// vars
static float threshold1 = 2500;
static float threshold2;
static float rr_average1;
static float rr_average2;
static float rr_low = 0;
static float rr_high = 99999;
static float rr_miss;
static float spkf = 5000;
static float npkf = 1000;

static peak peaks[PEAK_BUFFER_SIZE];
static peak r_peaks[R_PEAK_BUFFER_SIZE];

static float rr[R_PEAK_BUFFER_SIZE];
static float rr_ok[R_PEAK_BUFFER_SIZE];

static int rr_count = 0;
static int rr_ok_count = 0;

peak_update update_peak(int *mwi, int time);

#endif
