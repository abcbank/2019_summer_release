//a la russe algorithm
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main(void) {
    LARGE_INTEGER freq, start, stop;
	double diff;
	int *temp, *c, a, tmp, b, output=0, size = 0;
	
    printf("input A : ");
	scanf("%d", &a);
	printf("input B : ");
	scanf("%d", &b);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	tmp = a;

    while (tmp >= 1) {
		size++;
		tmp=tmp >> 1;
	}

	c = (int *)calloc(size, sizeof(int));
	temp = c;
	while (a >= 1) {
		if (a % 2) {
			*temp = b;
			temp++;
		}
		else {
			*temp == 0;
			temp++;
		}
		a = a >> 1;
		b = b << 1;
	}
	for(tmp=0;tmp<size;tmp++) {
		output += *(c+tmp);
	}
	printf("output : %d", output);
	free(c);
    //algorithm

    QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("수행 시간 : %f\n", diff);
	//required time
}