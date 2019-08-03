#include<stdio.h>
#include<stdlib.h>

int sumAB(int a, int b);
int mulAB(int a, int b);
int main() {
	int a, b, n, result;
	while (1) {
	// 무한 루프
		printf("1 : ADD\t2 : MUL\t3 : QUIT\n");
		scanf_s("%d", &n);
		// 메뉴 입력
		if (n == 3)
			break;
		printf("a : ");
		scanf_s("%d", &a);
		printf("b : ");
		scanf_s("%d", &b);
		switch (n) {
		// switch, case : n의 값에 따라 case를 구분, 해당된 구문만 실행
		case 1: result = sumAB(a, b);
			printf("%d + %d = %d\n", a, b, result);
			break;
			// break 없으면 case 2 내부 구문 또한 확인 후 실행한다.
		case 2: result = mulAB(a, b);
			printf("%d * %d = %d\n", a, b, result);
			break;
		default: break;
		}
	}
	return 0;
}

int sumAB(int a, int b) {
	return a + b;
}

int mulAB(int a, int b) {
	return a * b;
}