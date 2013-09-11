#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"

int main() {
	init_sensor("test_data/ECG.txt");

	int max = 10000;
	int idx = max;
	while (idx--) {
		printf("%i: %i\n", max - idx, get_next_data());
	}

	destroy_sensor();
	return 0;
}
