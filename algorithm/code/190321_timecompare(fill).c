// alg2
#include<stdio.h>
#include<Windows.h>
#define LINE 1
#define COLOR 2
#define seedx 3
#define seedy 3
#define seedLine 4
#define seedout 1
#define SIZE 7
#define STACK_MAX 1000000

#define push(data) (stack[++index] = data)
#define pop() (stack[index--])
#define delStack() (free(stack))
#define is_stack_empty() (index<0)

void recursiveFill_A(int x, int y);
void recursiveFill_B(int x, int y);
void recursiveFill_C(int x, int y);

void nrFill_A(int x, int y);
void nrFill_B(int x, int y);
void nrFill_C(int x, int y);

int **canvas;
int *stack;
int index;

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

void initStack() {
	index = -1;
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
	LARGE_INTEGER freq, start, stop, nrstart, nrstop;
	double diff;

	stack = (int*)malloc(STACK_MAX*sizeof(int));

	QueryPerformanceFrequency(&freq); // computer frequency
	initCanvas();

	QueryPerformanceCounter(&start); // starting point

	recursiveFill_A(seedx, seedy);
	printCanvas();

	QueryPerformanceCounter(&stop); // stopping point

	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("required time : %f\n\n", diff);

	delCanvas();
	initCanvas();

	QueryPerformanceCounter(&nrstart); // starting point

	nrFill_A(seedx, seedy);
	printCanvas();

	QueryPerformanceCounter(&nrstop); // stopping point

	diff = (double)(nrstop.QuadPart - nrstart.QuadPart) / freq.QuadPart;
	printf("required time : %f\n\n", diff);

	delCanvas();
	initCanvas();

	QueryPerformanceCounter(&start); // starting point

	recursiveFill_B(seedout, seedout);
	printCanvas();

	QueryPerformanceCounter(&stop); // stopping point

	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("required time : %f\n\n", diff);

	delCanvas();
	initCanvas();

	QueryPerformanceCounter(&nrstart); // starting point

	nrFill_B(seedout, seedout);
	printCanvas();

	QueryPerformanceCounter(&nrstop); // stopping point

	diff = (double)(nrstop.QuadPart - nrstart.QuadPart) / freq.QuadPart;
	printf("required time : %f\n\n", diff);

	delCanvas();
	initCanvas();

	QueryPerformanceCounter(&start); // starting point

	recursiveFill_C(seedLine, seedLine);
	printCanvas();

	QueryPerformanceCounter(&stop); // stopping point

	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("required time : %f\n\n", diff);

	delCanvas();
	initCanvas();

	QueryPerformanceCounter(&nrstart); // starting point

	nrFill_C(seedLine, seedLine);
	printCanvas();

	QueryPerformanceCounter(&nrstop); // stopping point

	diff = (double)(nrstop.QuadPart - nrstart.QuadPart) / freq.QuadPart;
	printf("required time : %f\n\n", diff);

	delCanvas();
	while (1);
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

// seed inside
void nrFill_A(int x, int y) {
	int cy, cx;
	initStack();

	push(x);
	push(y);

	while (!is_stack_empty()) {
		cy = pop();
		cx = pop();
		if (canvas[cy][cx] == 0) {
			canvas[cy][cx] = COLOR;
			push(cx - 1);
			push(cy);

			push(cx);
			push(cy - 1);

			push(cx + 1);
			push(cy);

			push(cx);
			push(cy + 1);
		}
	}
}

//seed outside
void nrFill_B(int x, int y) {
	int cy, cx;
	initStack();

	push(x);
	push(y);

	while (!is_stack_empty()) {
		cy = pop();
		cx = pop();
		if (canvas[cy][cx] == 0) {
			canvas[cy][cx] = COLOR;
			if (cx > 0) {
				push(cx - 1);
				push(cy);
			}

			if (cy > 0) {
				push(cx);
				push(cy - 1);
			}

			if (cx < 6) {
				push(cx + 1);
				push(cy);
			}

			if (cy < 6) {
				push(cx);
				push(cy + 1);
			}
		}
	}
}

// seed on line
void nrFill_C(int x, int y) {
	int cy, cx;
	initStack();

	push(x);
	push(y);

	while (!is_stack_empty()) {
		cy = pop();
		cx = pop();
		if (canvas[cy][cx] == 1) {
			canvas[cy][cx] = COLOR;
			push(cx - 1);
			push(cy);

			push(cx);
			push(cy - 1);

			push(cx + 1);
			push(cy);

			push(cx);
			push(cy + 1);

			push(cx + 1);
			push(cy + 1);

			push(cx - 1);
			push(cy - 1);

			push(cx + 1);
			push(cy - 1);

			push(cx - 1);
			push(cy + 1);
		}
	}
}