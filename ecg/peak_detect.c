#include "peak_detect.h"

#ifndef _PEAK_DETECT_C_
#define _PEAK_DETECT_C_

int update_peak(int *mwi, int time, float *pulseOut, peak *r_peak, peak *n_peak) {
	// r-peak flag
	int is_r_peak = 0;
	int p = 0;

	peak pk;
	pk.value = mwi[1];
	if (mwi[0] < pk.value && pk.value > mwi[2]) {
		pk.time = time;
		prepend_array_peak(peaks, PEAK_BUFFER_SIZE2, pk);
		
		// check if peak is noise or r-peak
		if (pk.value > threshold1) {
			if (time > 0)
				pk.interval = time - peaks[1].time;
			else 
				pk.interval = time;


			// is peak value between rr low and rr high
			if (pk.interval > rr_low && pk.interval < rr_high) {
				if (p) printf("\n\nR! %i - %f\n\n", pk.interval, rr_miss);

				// inc counts
				rr_count++;
				rr_ok_count++;

				// store peak as r-peak
				prepend_array_peak(r_peaks, PEAK_BUFFER_SIZE, pk);
				is_r_peak = 1;

				// store RR in all and ok
				prepend_array_float(rr, PEAK_BUFFER_SIZE, pk.interval);
				prepend_array_float(rr_ok, PEAK_BUFFER_SIZE, pk.interval);

				rr_average1 = array_average_float(rr, min_int(rr_count, PEAK_BUFFER_SIZE));
				rr_average2 = array_average_float(rr_ok, min_int(rr_ok_count, PEAK_BUFFER_SIZE));

				rr_low = 0.92 * rr_average2;
				rr_high = 1.16 * rr_average2;
				rr_miss = 1.66 * rr_average2;

				threshold1 = npkf + 0.25 * (spkf - npkf);
				threshold2 = 0.5 * threshold1;
				spkf = 0.125 * mwi[0] + 0.875 * spkf;
			}
			else if (pk.interval > rr_miss) {
				if (p) printf("\n\nS! %i - %f\n\n", pk.interval, rr_miss);
				// do searchback
				int idx = 0;
				peak peak2 = peaks[0];
				while (peak2.value != 0) {
					//printf("\nPeak2.value: %i threshold2:%f\n", peak2.value, threshold2);
					if (peak2.value > threshold2) {
						is_r_peak = 1;
						prepend_array_peak(r_peaks, PEAK_BUFFER_SIZE, pk);

						// store RR in all
						rr_count++;
						prepend_array_float(rr, PEAK_BUFFER_SIZE, peak2.interval);

						rr_average1 = array_average_float(rr, min_int(rr_count, PEAK_BUFFER_SIZE));

						rr_low = 0.92 * rr_average1;
						rr_high = 1.16 * rr_average1;
						rr_miss = 1.66 * rr_average1;

						spkf = 0.125 * peak2.value + 0.875 * spkf;
						threshold1 = npkf + 0.25 * (spkf - npkf);
						threshold2 = 0.5 * threshold1;

						break;
					}
					peak2 = peaks[++idx];
				}
			} 
			else {
				if (p) printf("\n\nM! %i - %f\n\n", pk.interval, rr_miss);
			}
		}
		else {		
			if (p) printf("\n\nN! %i - %f\n\n", pk.value, threshold1);
			
			// NB skiftet npkf til sidste
			npkf = 0.125 * pk.value + 0.875 * npkf;
			threshold1 = npkf + 0.25 * (spkf - npkf);
			threshold2 = 0.5 * threshold1;
		}
	}
	
	*pulseOut = rr_average1;
	*r_peak = r_peaks[0];
	*n_peak = peaks[0];
	return is_r_peak;
}

#endif
