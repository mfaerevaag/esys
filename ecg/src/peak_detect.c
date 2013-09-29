#include "peak_detect.h"

#ifndef _PEAK_DETECT_C_
#define _PEAK_DETECT_C_

peak_update update_peak(int *mwi, int time) {
	static int total_r_peaks = 0;
	static int consec_missed = 0;

	peak_update updt;
	updt.found_r_peak = 0;
	updt.missed = 0;

	peak pk;
	pk.value = mwi[1];

	// find peak
	if (mwi[0] < pk.value && pk.value > mwi[2]) {
		pk.time = time;
		
		// store peak
		prepend_array_peak(peaks, PEAK_BUFFER_SIZE, pk);
		
		// check if peak is noise or r-peak
		if (pk.value > threshold1) {

			// calculate RR
			pk.interval = time - r_peaks[0].time;

			// check missed beat
			if (!(pk.interval > rr_low && pk.interval < rr_high))
				updt.missed = 1;

			// is peak value between rr low and rr high
			if (pk.interval > rr_low && pk.interval < rr_high) {
				// reset misses
				consec_missed = 0;

				// mark as r peak
				updt.found_r_peak = 1;

				// inc counts
				rr_count++;
				rr_ok_count++;

				// store peak as r-peak
				prepend_array_peak(r_peaks, R_PEAK_BUFFER_SIZE, pk);
				
				// store rr in all and ok
				prepend_array_float(rr_ok, R_PEAK_BUFFER_SIZE, pk.interval);
				prepend_array_float(rr, R_PEAK_BUFFER_SIZE, pk.interval);

				rr_average1 = array_average_float(rr, min_int(rr_count, R_PEAK_BUFFER_SIZE));
				rr_average2 = array_average_float(rr_ok, min_int(rr_ok_count, R_PEAK_BUFFER_SIZE));

				rr_low = 0.92 * rr_average2;
				rr_high = 1.16 * rr_average2;
				rr_miss = 1.66 * rr_average2;
				
				spkf = 0.125 * pk.value + 0.875 * spkf;
				threshold1 = npkf + 0.25 * (spkf - npkf);
				threshold2 = 0.5 * threshold1;
			}
			else if (pk.interval > rr_miss) {
				// do searchback
				int idxx = 1;
				peak peak2 = peaks[idxx];
				while (peak2.value != 0) {
					if (peak2.value > threshold2) {
						// mark as r peak
						updt.found_r_peak = 1;

						// store peak in r-peaks
						prepend_array_peak(r_peaks, R_PEAK_BUFFER_SIZE, peak2);

						// store rr in rr
						rr_count++;
						prepend_array_float(rr, R_PEAK_BUFFER_SIZE, pk.interval);

						rr_average1 = array_average_float(rr, min_int(rr_count, R_PEAK_BUFFER_SIZE));
						
						rr_low = 0.92 * rr_average1;
						rr_high = 1.16 * rr_average1;
						rr_miss = 1.66 * rr_average1;

						spkf = 0.125 * pk.value + 0.875 * spkf;
						threshold1 = npkf + 0.25 * (spkf - npkf);
						threshold2 = 0.5 * threshold1;

						break;
					}
					
					peak2 = peaks[++idxx];
				}
			} else {
				// This is a noise peak, do nothing
			}
		}
		else {	
			npkf = 0.125 * pk.value + 0.875 * npkf;
			threshold1 = npkf + 0.25 * (spkf - npkf);
			threshold2 = 0.5 * threshold1;
		}
	}

	if (updt.found_r_peak)
		total_r_peaks++;

	if (updt.missed)
		consec_missed++;


	// fill in the rest of the update
	updt.pulse = rr_average1;
	updt.r_peak = r_peaks[0];
	updt.n_peak = peaks[0];
	updt.num_r_peaks = total_r_peaks;
	updt.consec_missed = consec_missed;

	return updt;
}

#endif
