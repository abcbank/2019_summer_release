#include<stdio.h>
int count = 0;
void move(int from, int to) {
	printf("\nMove %d to %d", from, to);
	count++;
}

void hanoi(int n, int from, int by, int to) {
	if (n == 1)
		move(from, to);
	else {
		hanoi(n - 1, from, to, by);
		move(from, by);
		hanoi(n - 1, by, from, to);
	}
}

void main() {
	int j = 0;
	while (1) {
		printf("Input(-1 to end) : ");
		scanf_s("%d", &j);
		if (j == -1)
			break;
		hanoi(j, 1, 2, 3);
		printf("\nmove count : %d\n", count);
		count = 0;
	}
}