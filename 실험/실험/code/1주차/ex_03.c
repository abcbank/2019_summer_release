#include<stdio.h>
#include<stdlib.h>

int main() {
	printf("Data types and sizes\n\n");
	printf("char = %d bytes\nint = %d bytes\n", sizeof(char), sizeof(int));
	printf("short = %d bytes\nlong = %d bytes\n", sizeof(short), sizeof(long));
	printf("float = %d bytes\ndouble = %d bytes\n", sizeof(float), sizeof(double));
}