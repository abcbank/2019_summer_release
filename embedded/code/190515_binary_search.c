#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 10000
#define MAX_SIZE 10000
#define notprint 0
#define UNSEEN -INT_MAX
#define MAX_NODE 10000
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')

int stack[MAX_SIZE];
int top;

void gen_nr_quick_sort(void *base, size_t N, size_t width, int(*fcmp)(const void *, const void *));

int intcmp(const void *a, const void *b)
{
	return (*(char *)a > *(char *)b);
}

// stack function
void push(int data) {
	stack[++top] = data;
}

int pop() {
	return stack[top--];
}

int stack_empty() {
	return top == -1;
}

void init_stack() {
	top = -1;
}
// end stack function

int improved_bi_search(int key, char *a, int N)
{
	int mid;
	int left = 0;
	int right = N - 1;
	while (right >= left) {
		mid = left + (float)(key - a[left])*(right - left) / (a[right] - a[left]);
		if (key == a[mid]) return mid;
		if (key < (int)a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int bi_insert(int key, char *a, int *N)
{
	int p = 0;
	int i;
	while (key > a[p] && p < *N)
		p++;
	for (i = *N; i > p; i--)
		a[i] = a[i - 1];
	a[p] = key;
	(*N)++;
	return p;
}

int bi_delete(int key, int *a, int *N)
{
	int p;
	int i;
	if (*N > 0) {
		if ((p = bi_search(key, a, *N) < 0))
			return -1;
			for (i = p + 1; i < *N; i++)
				a[i - 1] = a[i];
			(*N)--;
			return p;
	}
	return -1;
}

void main() {
	char str[20] = "TOSORTALGORITHM";
	int size = 15;

	int(*cmp)(const void *, const void *) = intcmp;
	// Conduct sorting a str array (e.g., quick / heap sort)
	gen_nr_quick_sort(str, size, sizeof(char), cmp);
	// Find a specific character using binary search
	int p = bi_search('S', str, size);
	printf("Find your key at %d(value %c)\n", p, str[p]);
	// Insert and delete a specific character
	p = bi_insert('Z', str, &size); // or p = bi_delete(‘A’, str, &size);
	printf("%s\n", str);
}

void gen_nr_quick_sort(void *base, size_t N, size_t width, int(*fcmp)(const void *, const void *)) {
	void *pivot = malloc(width);
	void *temp = malloc(width);
	int bottom = 0, ceiling = N - 1;
	int up2down, down2up;
	init_stack();
	push(bottom);
	push(ceiling);
	while (!stack_empty()) {
		ceiling = pop();
		bottom = pop();
		if (ceiling - bottom > 0) {
			memcpy(pivot, (char*)base + ceiling * width, width);
			down2up = bottom - 1;
			up2down = ceiling;
			while (1) {
				while (fcmp(pivot, (char*)base + (++down2up)*width));
				while (fcmp((char*)base + (--up2down)*width, pivot));
				if (down2up > up2down) break;
				memcpy(temp, (char*)base + down2up * width, width);
				memcpy((char*)base + down2up * width, (char*)base + up2down * width, width);
				memcpy((char*)base + up2down * width, temp, width);
			}

			memcpy(temp, (char*)base + ceiling * width, width);
			memcpy((char*)base + ceiling * width, (char*)base + down2up * width, width);
			memcpy((char*)base + down2up * width, temp, width);
			push(down2up);
			push(ceiling);
			push(bottom);
			push(down2up - 1);
		}
	}
}