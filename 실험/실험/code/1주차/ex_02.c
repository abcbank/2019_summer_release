#include<stdio.h>
#include<stdlib.h>

int main() {
	float fahr = 0, celesius;		// fahr : 화씨, celesius : 도씨
	int lower, upper, step;			// upper : break point, step : 증가량

	lower = 0;						
	upper = 300;					// break point = 200
	step = 20;						// 증가량 = 20
	while (fahr <= upper) {
		celesius = (5.0 / 9.0)*(fahr - 32.0); // (도씨 온도) = 5/9*(화씨-32) 
		printf("fahr : %3.0f celesius : %6.1f\n", fahr, celesius);	
		// %3.0f, %6.1f : %(n칸 기준 오른쪽 정렬).(소수점 아래 자리 갯수)f
		// %f	-> 14.14
		// %5.1f->  14.1
		fahr = fahr + step; // 화씨에 증가량을 더함
	}
	return 0;
}
