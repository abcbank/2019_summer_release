#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void main() {
	int count=0, i=0;
	char*c=(char*)calloc(1000,sizeof(char));

	printf("input : ");
	scanf("%[^\n]s", c);

	while (c[i]) {
		if (c[i++] == ' ')
			count++;
	}
	printf("output : %d", count);
	free(c);
}

// 64bit vs 32 bit 차이?
// 포인터를 사용하는 이유
// 배열의 이름이 가지는 의미 및 배열의 이름의 크기
// 메모리 주소를 사용한다 = OS 레벨에서 코딩한다
// %[^\n]s의 의미?
// gobal 변수와 포인터의 장단점
//main 함수에 매개변수가 있는 이유?
// console vs powershell