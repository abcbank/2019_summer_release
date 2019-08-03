//alg 1
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define BLK 20
#define x1 1
#define x2 19
#define y1 1
#define y2 19
#define STACK_MAX 1000000

#define push(data) (stack[++index] = data)
#define pop() (stack[index--])
#define is_stack_empty() (index<0)

int *canvas;
int *stack;
int index;

void nrLine(int a1, int b1, int a2, int b2);
void recursiveLine(int a1, int b1, int a2, int b2);

initCanvas() {
	canvas = (int*)calloc(BLK*BLK, sizeof(int));
}

void initStack() {
	index = -1;
}

void printCanvas() {
	for (int i = 0; i < BLK; i++) {
		for (int j = 0; j < BLK; j++) {
			printf("%-2d", canvas[BLK*i + j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

void main() {
	int xfrom,yfrom, xto, yto;
	LARGE_INTEGER freq, start, stop, nrstart, nrstop;
	double diff;

	stack = (int*)malloc(sizeof(int)*STACK_MAX);
	while (1) {
		initCanvas();
		printf("Input(x1,y1) : ");
		scanf_s("%d %d", &xfrom, &yfrom);
		printf("Input(x2,y2) : ");
		scanf_s("%d %d", &xto, &yto);

		if (xfrom < 0 || yfrom < 0|| xto <0 || yto < 0) {
			printf("default value\n\n");
			xfrom = x1;
			yfrom = y1;
			xto = x2;
			yto = y2;
		}
		canvas[BLK * yfrom + xfrom] = 1;
		canvas[BLK * yto + xto] = 1;

		QueryPerformanceFrequency(&freq); // computer frequency

		QueryPerformanceCounter(&start); // starting point

		recursiveLine(xfrom, yfrom, xto, yto);	//recursive

		QueryPerformanceCounter(&stop); // stopping point

		diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
		//required time(recursive)

		printCanvas();
		printf("required time : %f\n\n", diff);

		free(canvas);
		// free canvas
		initCanvas();
	
		canvas[BLK * yfrom + xfrom] = 1;
		canvas[BLK * yto + xto] = 1;

		QueryPerformanceCounter(&nrstart); // starting point

		nrLine(xfrom, yfrom, xto, yto);

		QueryPerformanceCounter(&nrstop); // stopping point

		diff = (double)(nrstop.QuadPart - nrstart.QuadPart) / freq.QuadPart;

		//required time,nr
		printCanvas();
		
		printf("required time : %f\n\n", diff);
		free(canvas);
	}
	free(stack);
	while (1);
}

void nrLine(int a1, int b1, int a2, int b2) {
	int ax,ay,bx,by, avrx, avry;
	initStack();
	push(a1);
	push(b1);
	push(a2);
	push(b2);
	while (!is_stack_empty()) {
		by = pop();
		bx = pop();
		ay = pop();
		ax = pop();

		if (abs(bx-ax) > 1 || abs(by-ay) > 1) {
			avrx = (ax + bx) / 2;
			avry = (ay + by) / 2;
			canvas[BLK*avry + avrx] = 1;
			push(avrx);
			push(avry);
			push(bx);
			push(by);

			push(ax);
			push(ay);
			push(avrx);
			push(avry);
		}
	}
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