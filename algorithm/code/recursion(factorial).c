#include<stdio.h>

void factorial(int n, int *result) {
	for (int i = 1; i <= n; i++) {
		*result *= i;
	}
}

int factorial_recursion(int n, int result) {
	if (n == 0){
		return 1;
	}
	else {
		return n*factorial_recursion(n - 1, result);
	}
}

void main() {
	int n = 0, result = 1;
	printf("Input : ");
	scanf_s("%d", &n);
	factorial(n, &result);
	printf("w/o recursion : %d\n", result);
	result = 1;
	printf("w/ recursion : %d\n", factorial_recursion(n, result));
}