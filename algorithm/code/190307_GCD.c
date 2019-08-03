#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int GCD_minus(int A, int B);
int GCD_mod(int A, int B);


void main() {
	int A, B;
	int minus, mod;
	LARGE_INTEGER freq, start, stop;
	double diff_minus, diff_mod;
	printf("input : ");
	scanf("%d %d", &A, &B);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	minus = GCD_minus(A, B);

	QueryPerformanceCounter(&stop); // stopping point
	diff_minus = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	mod = GCD_mod(A, B);

	QueryPerformanceCounter(&stop); // stopping point
	diff_mod = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("GCD_minus : %d\ndiff_minus : %f\n", minus, diff_minus);
	printf("GCD_mod : %d\ndiff_mod : %f\n", mod, diff_mod);
}

int GCD_minus(int A, int B) {
    if(B==0)
        return A;
    A<B ? GCD_minus(B,A) : GCD_minus(A-B,B);
}

int GCD_mod(int A, int B) {
	if(B==0)
        return A;
    A<B ? GCD_mod(B,A) : GCD_minus(A%B,B);
}