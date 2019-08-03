#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<math.h>
#define HEIGHT 44
#define WIDTH 45
#define WIDTHBYTES(bits) (((bits)+31)/32*4) 
#define BYTE unsigned char
#define MIDDLE(x,y,width) (y*width + x)
#define WEST(x,y,width) (y*width + x - 1)
#define EAST(x,y,width) (y*width + x + 1)
#define NORTH(x,y,width) ((y-1)*width + x)
#define SOUTH(x,y,width) ((y+1)*width+x)
#define NORTHEAST(x,y,width) ((y-1)*width+x+1)
#define SOUTHEAST(x,y, width) ((y+1) * width + x+1)
#define SOUTHWEST(x,y,width) ((y+1) * width + x-1)
#define NORTHWEST(x,y,width) ((y-1)*width + x -1)
#define INCLUDEGRAPH 1
#define MAX_SIZE 10000

int stack[MAX_SIZE];
int top;

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

FILE *fp;// 파일 포인터 선언
BYTE lineFilter[3];
BYTE azimuth4Filter[5];
BYTE azimuth8Filter[9];
BYTE *source;
BYTE *result;
int mode;

void read(BYTE* data, int height, int width);
void medianFiltering_line(BYTE *src,BYTE *dst, int height, int width);
void print(BYTE *src, int height, int width);
void datacpy(BYTE *src, BYTE *dst, int height, int width);
void medianFiltering_4azimuth(BYTE *src, BYTE *dst, int height, int width);
void medianFiltering_8azimuth(BYTE *src, BYTE *dst, int height, int width);
void datacharacter(BYTE *data, int height, int width);
BYTE sorting(BYTE *data, int size);

void main() {
	int width = WIDTH;
	int height = HEIGHT;

	source = (BYTE*)malloc(width*height * sizeof(BYTE));
	result = (BYTE*)malloc(width*height * sizeof(BYTE));
	printf("Print Graph in Data Character?\n");
	printf("1. Yes\t2. No\n");
	printf(">> ");
	scanf("%d", & mode);
	read(source, height, width);
	printf("Default Data");
//	print(source, height, width);
//	datacharacter(source, height, width);

	printf("\n\nLine Filter");
	datacpy(source, result, height, width);
	medianFiltering_line(source, result, height, width);
	print(result, height, width);
	datacharacter(result, height, width);

	printf("\n\n4-defenses Filter");
	datacpy(source, result, height, width);
	medianFiltering_4azimuth(source, result, height, width);
	print(result, height, width);
	datacharacter(result, height, width);

	printf("\n\n8-defenses Filter");
	datacpy(source, result, height, width);
	medianFiltering_8azimuth(source, result, height, width);
	print(result, height, width);
	datacharacter(result, height, width);

	while (1);
}

void datacpy(BYTE *src, BYTE *dst, int height, int width) {
	for (int i = 0; i < height*width; i++)
		*dst++ = *src++;
}

void print(BYTE *src, int height, int width) {
	for (int i = 0; i < height; i++) {
		printf("\n");
		for (int j = 0; j < width; j++) {
			printf("%4d", *src++);
		}
	}

	printf("\n");
}

void read(BYTE* data, int height, int width) {
	int a=0;
	printf("get text data\n\n");
	fp = fopen("noisy_data.txt", "r");

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fscanf(fp, "%d", &a);
			*data++ = (BYTE)a;
		}
	}
	fclose(fp);
}

void datacharacter(BYTE *data, int height, int width) {
	int graph[256] = { 0 };
	int temp;
	float average = 0;
	float variance = 0;
	for (int i = 0; i < width*height; i++) {
		graph[data[i]]++;
	}

	if (mode == INCLUDEGRAPH) {
		for (int i = 0; i < 256; i++) {
			printf("\n%3d : %d\n", i, graph[i]);
			// 각주 -> graph 값만큼 *개수로 표기
			//printf("\n%3d\n", i);
			//for (int j = 0; j < graph[i]; j++)
			//	printf("*");
		}
	}

	for (int i = 0; i < 256; i++) {
		average += i * graph[i];
	}
	average /= width * height;
	printf("\nAverage : %f", average);

	for (int i = 0; i < 256; i++) {
		variance += (i - average)*(i - average)*graph[i] / 256;
	}
	printf("\nVariance : %f", variance);
}

void medianFiltering_line(BYTE *src, BYTE *dst, int height, int width) {
	for (int y = 0; y < height; y++) {
		for (int x = 1; x < width-1; x++) {
			lineFilter[0] = src[WEST(x, y, width)];
			lineFilter[1] = src[MIDDLE(x, y, width)];
			lineFilter[2] = src[EAST(x, y, width)];
			dst[MIDDLE(x, y, width)] = sorting(lineFilter, sizeof(lineFilter));
		}
	}
}

void medianFiltering_4azimuth(BYTE *src, BYTE *dst, int height, int width) {
	for (int y = 1; y < height-1; y++) {
		for (int x = 1; x < width - 1; x++) {
			azimuth4Filter[0] = src[WEST(x, y, width)];
			azimuth4Filter[1] = src[MIDDLE(x, y, width)];
			azimuth4Filter[2] = src[EAST(x, y, width)];
			azimuth4Filter[3] = src[SOUTH(x, y, width)];
			azimuth4Filter[4] = src[NORTH(x, y, width)];
			
			dst[MIDDLE(x, y, width)] = sorting(azimuth4Filter, sizeof(azimuth4Filter));
		}
	}
}

void medianFiltering_8azimuth(BYTE *src, BYTE *dst, int height, int width) {
	for (int y = 1; y < height-1; y++) {
		for (int x = 1; x < width - 1; x++) {
			azimuth8Filter[0] = src[WEST(x, y, width)];
			azimuth8Filter[1] = src[MIDDLE(x, y, width)];
			azimuth8Filter[2] = src[EAST(x, y, width)];
			azimuth8Filter[3] = src[SOUTH(x, y, width)];
			azimuth8Filter[4] = src[NORTH(x, y, width)];
			azimuth8Filter[5] = src[SOUTHEAST(x, y, width)];
			azimuth8Filter[6] = src[SOUTHWEST(x, y, width)];
			azimuth8Filter[7] = src[NORTHEAST(x, y, width)];
			azimuth8Filter[8] = src[NORTHWEST(x, y, width)];

			dst[MIDDLE(x, y, width)] = sorting(azimuth8Filter, sizeof(azimuth8Filter));
		}
	}
}

BYTE sorting(BYTE *base, int size) {
	int pivot, temp;
	int bottom = 0, ceiling = size - 1;
	// 각각 while문 내에서 바닥과 천장을 알려주는 역할
	int up2down, down2up;
	// 위에서 아래로 내려가는 index, 아래에서 위로 올라가는 index
	init_stack();

	push(bottom);
	push(ceiling);

	while (!stack_empty()) {
		ceiling = pop();
		bottom = pop();
		// 바닥과 천장을 pop
		if (ceiling - bottom > 0) {
			// 바닥과 천장이 같으면 해당 배열의 크기는 1이다. 따라서 정렬을 해줄 필요가 없다. 
			pivot = base[ceiling];
			// 마지막 항을 pivot이라 설정
			down2up = bottom - 1;
			up2down = ceiling;
			// 양 끝에 index 설정. pre-increase system이므로 1씩 빼준다.
			while (1) {
				while (base[++down2up] < pivot);
				while (base[--up2down] > pivot);
				if (down2up > up2down) break;
				temp = base[down2up];
				base[down2up] = base[up2down];
				base[up2down] = temp;
			}
			temp = base[ceiling];
			base[ceiling] = base[down2up];
			base[down2up] = temp;
			// re와 알고리즘 동일

			push(down2up);
			push(ceiling);
			// pivot보다 숫자가 큰 부분의 시작과 끝 index를 push해준다.
			push(bottom);
			push(down2up - 1);
			// pivot보다 숫자가 작은 부분의 시작과 끝 index를 push해준다.
		}
	}
	return base[size / 2];
}
