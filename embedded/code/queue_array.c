#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')

char sq[MAX_SIZE];
int front;
int rear;

void init_sq() {
	front = 0;
	rear = 0;
}

int put_sq(int k) {
	if ((rear + 1) % MAX_SIZE == front) {
		printf("Queue overflow!\n\n");
		return -1;
	}
	rear = rear%MAX_SIZE;
	sq[rear++] = k;

	return k;
}

int get_sq() {
	int j;
	if (front == rear) {
		printf("Queue underflow!\n\n");
		return-1;
	}
	j = sq[front];
	front = ++front%MAX_SIZE;
	return j;
}
void print_queue()
{
	int k;
	for (k = front; k != rear; k = ++k%MAX_SIZE)
		printf("%-6d", sq[k]);
}

int main(void) {
	int k;
	init_sq();

	put_sq(3);
	put_sq(6);
	put_sq(9);
	put_sq(1);
	put_sq(6);
	put_sq(3);
	print_queue();

	put_sq(4);
	put_sq(8);
	put_sq(7);
	put_sq(2);
	put_sq(0);
	init_sq();

	get_sq();
}