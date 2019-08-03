#include<stdio.h>
#include<stdlib.h>

void statistic(int *arr, int arr_size, float *avr, int * max, int *min) {
	float sum = 0;
	int fi = 0;
	*min = INT_MAX;
	*max = INT_MIN;

	for (fi = 0; fi < arr_size; fi++)
		if (arr[fi] > *max)
			*max = arr[fi];

	for (fi = 0; fi < arr_size; fi++)
		if (arr[fi] < *min)
			*min = arr[fi];

	for (fi = 0; fi < arr_size; fi++)
		sum += arr[fi++];
	*avr = sum / arr_size;
}

int main(int argc, char *argv[]) {
	int n = 0;
	int *ptr = NULL;
	float avr = 0;
	int max = 0;
	int min = 0;
	int fi;

	srand((unsigned)time(NULL));
	if (argc < 2) {
		printf("check input\n");
		return -1;
	}

	n = atoi(argv[1]);
	if (n < 1) {
		printf("check input\n");
		return -1;
	}

	ptr = (int*)malloc(n * sizeof(int));
	for (fi = 0; fi < n; fi++) {
		*(ptr + fi) = rand() % 100 + 1;
		printf("ptr[%d] : %d\n", fi, *(ptr + fi));
	}
	statistic(ptr, n, &avr, &max, &min);
	printf("avr : %f, max : %d, min : %d\n", avr, max, min);
	while (1);
}

//C:\Users\MSI\source\repos\Project2\Debug\Project2.exe