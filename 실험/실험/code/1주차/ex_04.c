#include<stdio.h>
#include<stdlib.h>

int strlen(unsigned char *str);

int main() {
	int len;	//문자열의 길이를 저장할 변수
	unsigned char *str = "Some where over the rainbow";	//지정된 문장을 문자열에 대입
	printf("strlen : return length of string\n");
	printf("string = \"%s\"\n", str);	//\" -> 출력창에 " 쓰기
	len = strlen(str);	// 선언된 함수를 통해 문자열의 길이를 len변수에 대입
	printf("strlen : %d\n", len);	// 문자열의 길이 출력
}

int strlen(unsigned char *str) {
	int i = 0;
	while (str[i] != NULL) {	// str[i]가 NULL, 즉 종료 문자가 아니면 i값 증가
		i++;
	}
	return i;
}