#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define push(data) (stack[++top]=data)
#define pop() (stack[top--])
#define is_stack_empty() (top<0)
#define MAX 1000000

int *stack;
int top;
int count = 0;

void move(int from, int to) {
	count++;
	printf("%d에서 %d로 이동\n",from,to);
}
void init_stack() {
	free(stack);
	stack = (int *)calloc(MAX, sizeof(int));
}
void nr_hanoi(int n, int from, int by, int to) {
	int done = 0;
	init_stack();
	while (!done) {
		while (n != 1) {
			if (top < MAX - 2) push(to);
			if (top < MAX - 2) push(by);
			if (top < MAX - 2) push(from);
			if (top < MAX - 2) push(n);

			n--;
			if (top < MAX - 2) push(top);
			to = by;
			by = pop();
		}
		move(from, to);
		if (!is_stack_empty()) {
			n = pop();
			from = pop();
			by = pop();
			to = pop();
			move(from, to);
			n--;
			if (top < MAX - 2) push(from);
			from = by;
			by = pop();
		}
		else done = 1;
	}
}
int main() {
	stack = (int *)calloc(MAX, sizeof(int));
	top = -1;

	nr_hanoi(10, 1, 2, 3);
	printf("이동 횟수 : %d", count);
}