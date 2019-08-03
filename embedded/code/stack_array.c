#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_STACK 9

int stack[MAX_STACK];
int top;

int init_stack() {
	return top = -1;
}

int push(int i) {
	if (top >= MAX_STACK - 1) {
		printf("Stack overflow \n");
		return -1;
	}

	return stack[++top] = i;
}

int pop() {
	if (top < 0) {
		printf("Stack underflow\n");
		return -1;
	}

	return stack[top--];
}

int print_stack(int a[]) {
	for (int i = 0; i <= top; i++) {
		printf("%d member : %d\n", i + 1, a[i]);
	}
}

int main() {
	init_stack();
	push(3);
	push(6);
	push(9);
	push(1);
	push(6);

	print_stack(stack);

	push(4);
	push(8);
	push(7);
	push(2);
	push(0);

	print_stack(stack);

	init_stack();
	pop();

}