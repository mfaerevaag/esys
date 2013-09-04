#include <stdio.h>

static const char filename[] = "ECG.txt";

int main(int argc, const char * args[]) {
	FILE *file = fopen(filename, "r");
	int num;
	int max = 0;
	while (fscanf(file,"%i", &num) == 1) {
		if (num > max)
			max = num;
	}

	printf("Max er %i\n", max);

	return 0;
}
