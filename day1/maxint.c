#include <stdio.h>

int main(int argc, const char * args[]) {
	static const char filename[] = "ECG.txt";
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
