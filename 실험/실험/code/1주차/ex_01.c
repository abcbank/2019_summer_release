#include<stdio.h>
#include<stdlib.h>

#define sumAB(a,b) a+b
// 덧셈
#define mulAB(a,b) a*b
// 곱셈

int main() {
	int a, b, n, result;
	while (1) {
		printf("1 : ADD, 2 : MUL, 3 : quit\n");
		scanf_s("%d", &n);
		if (n == 3) {
			printf("exit program\n");
			break;
		}
		printf("a : ");
		scanf_s("%d", &a);
		printf("b : ");
		scanf_s("%d", &b);
		switch (n) {
        // n의 값에 따라 실행문이 달라진다.
		case 1: result = sumAB(a, b);
			printf("%d + %d = %d", a, b, result);
			break;
		case 2: result = mulAB(a, b);
			printf("%d + %d = %d", a, b, result);
			break;
		default: break;
		}
		printf("\n");
	}
	return 0;
}