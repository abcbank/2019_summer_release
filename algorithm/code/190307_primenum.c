#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<math.h>
//
typedef struct prime_array {
	int *mem;
	int MAX;
}numberset;

void isprime(numberset *root, int n);

int main(void) {
	numberset root;
	LARGE_INTEGER freq, start, stop;
	double diff;

	printf("input : ");
	scanf("%d", &root.MAX);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point
	root.mem = (int*)calloc(root.MAX + 1, sizeof(int));
	root.mem[0] = 1;
	root.mem[1] = 1;
	for (int n = 2; n <= root.MAX; n++) {
		if (root.mem[n] == 0)
			isprime(&root, n);
	}
	for (int n = 0; n < root.MAX; n++)
		if (root.mem[n] == 0)
			printf("%d\t", n);
	printf("\n");
	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("required time : %lf\n", diff);

}
void isprime(numberset *root, int n) {
	for (int a = 2; a <= (root->MAX) / n; a++) {
		root->mem[n*a] = 1;
	}
}