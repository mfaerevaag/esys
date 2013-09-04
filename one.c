#include <stdio.h>

static const char filename[] = "ECG.txt";

int main(int argc, const char * args[]) {
	FILE *file = fopen(filename, "r");
	int i1;
	fscanf(file,"%i", &i1);

	printf("Det er %i\n", i1);

	return 0;
}
