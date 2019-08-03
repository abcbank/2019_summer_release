// alg2
#include<stdio.h>
#define LINE 1
#define COLOR 2
#define seedx 3
#define seedy 3
#define seedLine 4
#define seedout 1
#define SIZE 7
void recursiveFill_A(int x, int y);
void recursiveFill_B(int x, int y);
void recursiveFill_C(int x, int y);
int **canvas;

void initCanvas() {
	canvas = (int**)malloc(SIZE * sizeof(int*));
	for (int i = 0; i < SIZE; i++)
		*(canvas + i) = (int*)calloc(SIZE, sizeof(int));
	canvas[1][2] = LINE;
	canvas[1][3] = LINE;
	canvas[1][4] = LINE;
	canvas[2][1] = LINE;
	canvas[2][5] = LINE;
	canvas[3][1] = LINE;
	canvas[3][5] = LINE;
	canvas[4][1] = LINE;
	canvas[4][4] = LINE;
	canvas[5][2] = LINE;
	canvas[5][3] = LINE;
	canvas[5][4] = LINE;
}

void delCanvas() {
	for (int i = 0; i < SIZE; i++)
		free(*(canvas + i));
	free(canvas);
}

void printCanvas() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%-2d", canvas[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	initCanvas();
	
	recursiveFill_A(seedx, seedy);
	
	printCanvas();

	delCanvas();
	initCanvas();

	recursiveFill_B(seedout,seedout);

	printCanvas();

	delCanvas();
	initCanvas();

	recursiveFill_C(seedLine,seedLine);
	printCanvas();

    delCanvas();
}

// point inside
void recursiveFill_A(int x, int y) {

	if (canvas[y][x] != 0) {
		return;
	}
	else {
		canvas[y][x] = COLOR;
		recursiveFill_A(x - 1, y);
		recursiveFill_A(x, y - 1);
		recursiveFill_A(x + 1, y);
		recursiveFill_A(x, y + 1);
	}
}

// point outside
void recursiveFill_B(int x, int y) {
	if (canvas[y][x] != 0) {
		return;
	}
	else {
		canvas[y][x] = COLOR;
		if (x >= 1) recursiveFill_B(x - 1, y);
		if (y >= 1) recursiveFill_B(x, y - 1);
		if (x < 6) recursiveFill_B(x + 1, y);
		if (y < 6) recursiveFill_B(x, y + 1);
	}
}

//point line
void recursiveFill_C(int x, int y) {
	if (canvas[y][x] != LINE)
		return;
	else {
		canvas[y][x] = COLOR; 
		recursiveFill_C(x - 1, y);
		recursiveFill_C(x, y - 1);
		recursiveFill_C(x + 1, y);
		recursiveFill_C(x, y + 1);
		recursiveFill_C(x - 1, y - 1);
		recursiveFill_C(x - 1, y + 1);
		recursiveFill_C(x + 1, y - 1);
		recursiveFill_C(x + 1, y + 1);

	}
}