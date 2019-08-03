// alg2
#include<stdio.h>
#define STACK_MAX 100000
#define LINE 1
#define COLOR 2
#define seedx 3
#define seedy 3
#define seedLine 4
#define seedout 1
#define SIZE 7

#define push(data) (stack[++index] = data)
#define pop() (stack[index--])
#define delStack() (free(stack))
#define is_stack_empty() (index<0)

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
	stack = (int*)malloc(sizeof(int)*STACK_MAX);
	initCanvas();

	nrFill_A(seedx, seedy);
	
	printCanvas();

	delCanvas();
	initCanvas();

	nrFill_B(seedout,seedout);

	printCanvas();

	delCanvas();
	delStack();

	initCanvas();

	nrFill_C(seedLine,seedLine);
	printCanvas();

	while (1);
}
// seed inside
void nrFill_A(int x, int y) {
	int cy,cx;
	initStack();
	
	push(x);
	push(y);
	
	while (!is_stack_empty()) {
		cy = pop();
		cx = pop();
		if (canvas[cy][cx] == 0) {
			canvas[cy][cx] = COLOR;
			push(cx-1);
			push(cy);
			
			push(cx);
			push(cy-1);
			
			push(cx+1);
			push(cy);

			push(cx);
			push(cy+1);
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
				push(cy-1);
			}
			
			if (cx < 6) {
				push(cx +1);
				push(cy);
			}
			
			if (cy < 6) {
				push(cx);
				push(cy+1);
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