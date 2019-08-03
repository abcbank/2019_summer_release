#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

int main(void) {
	LARGE_INTEGER freq, start, stop;
	double diff;
	int dice, num, test;
	int *result = (int *)calloc(6, sizeof(int));
	srand((unsigned int)time(NULL));

	printf("시행 횟수를 입력하시오 : ");
	scanf("%d", &test);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	for (num = 0; num < 6; num++)
		result[num] = 0;
	for (num = 0; num < test; num++) {
		dice = rand() % 6;
		result[dice]++;
	}
	for (num = 0; num < 6; num++)
		printf("%d : %d\n", num + 1, result[num]);
	printf("총 시행 횟수 : %d\n", result[0] + result[1] + result[2] + result[3] + result[4] + result[5]);
    free(result);
     //Algorithm

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("수행 시간 : %f\n", diff);
}
