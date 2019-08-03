#include<stdio.h>
#include<stdlib.h>

int main() {
	int i;
	int j = 0, k = 0;
	int m = 10, n = 10;
	for (i = 0; i < 10; i++)	
		printf("Increment : ++j = %2d, k++ = %2d\n", ++j, k++);
	// ++k : 해당 line을 실행하기 전에 k값에 1을 더함, k++ : 해당 line이 끝난 후 k값에 1을 더함
	printf("\n");
	for (i = 0; i < 10; i++)
		printf("Decrement : --m = %2d, n-- = %2d\n", --m, n--);
	while (1);
}