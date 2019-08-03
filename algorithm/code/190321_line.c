//alg 1
#include<stdio.h>
#include<stdlib.h>
#define BLK 20
#define x1 1
#define x2 19
#define y1 1
#define y2 19


void recursiveLine(int a1, int b1, int a2, int b2);

int *canvas;

void main() {
	int i, j;
	canvas = (int*)calloc(BLK*BLK, sizeof(int));

	canvas[BLK * y1 + x1] = 1;
	canvas[BLK * y2 + x2] = 1;
	recursiveLine(x1, y1, x2, y2);
	for (i = 0; i < BLK; i++) {
		for (j = 0; j < BLK; j++) {
			printf("%-2d", canvas[BLK*i + j]);
		}
		printf("\n");
	}
	while (1);
}

void recursiveLine(int a1, int b1, int a2, int b2) {
	if ((a2 - a1 <= 1) && (b2 - b1 <= 1)) {
		return;
	}
	else {
		int cy = (b1 + b2) / 2;
		int cx = (a1 + a2) / 2;
		canvas[BLK*cy + cx] = 1;
		recursiveLine(a1, b1, cx, cy);
		recursiveLine(cx, cy, a2, b2);
	}
}