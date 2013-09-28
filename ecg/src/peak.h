#include <stdlib.h>


#ifndef _PEAK_H_
#define _PEAK_H_

typedef struct peak_s {
	int value;
	int time;
	int interval;
} peak;

typedef struct peak_update_s {
	float pulse;
	peak r_peak;
	peak n_peak;
	int num_r_peaks;
	int found_r_peak;
	int missed;
	int consec_missed;
} peak_update;

#endif
