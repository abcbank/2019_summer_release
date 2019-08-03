#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<math.h>
#define HEIGHT 44
#define WIDTH 45
#define WIDTHBYTES(bits) (((bits)+31)/32*4) 
#define BYTE unsigned char
#define WEST(x,y,width) (y*width + x - 1)
#define EAST(x,y,width) (y*width + x + 1)
#define NORTH(x,y,width) ((y-1)*width + x)
#define SOUTH(x,y,width) ((y+1)*width+x)
#define NORTHEAST(x,y,width) ((y-1)*width+x+1)
#define SOUTHEAST(x,y, width) ((y+1) * width + x+1)
#define SOUTHWEST(x,y,width) ((y+1) * width + x-1)
#define NORTHWEST(x,y,width) ((y-1)*width + x -1)
#define INCLUDEGRAPH 1

FILE *fp;// 파일 포인터 선언
BYTE filter1[3];
BYTE *source;
BYTE *result;
int mode;

void read(BYTE* data, int height, int width);
void averageFiltering_line(BYTE *src,BYTE *dst, int height, int width);
void print(BYTE *src, int height, int width);
void datacpy(BYTE *src, BYTE *dst, int height, int width);
void averageFiltering_4defenses(BYTE *src, BYTE *dst, int height, int width);
void averageFiltering_8defenses(BYTE *src, BYTE *dst, int height, int width);
void datacharacter(BYTE *data, int height, int width);

void main() {
	int width = WIDTH;
	int height = HEIGHT;

	source = (BYTE*)malloc(width*height * sizeof(BYTE));
	result = (BYTE*)malloc(width*height * sizeof(BYTE));
	printf("Print Graph in Data Character?\n");
	printf("1. Yes\t2. No\n");
	printf(">>");
	scanf("%d", & mode);
	read(source, height, width);
	printf("Default Data");
//	print(source, height, width);
	datacharacter(source, height, width);

	printf("\n\nLine Filter");
	datacpy(source, result, height, width);
	averageFiltering_line(source, result, height, width);
//	print(result, height, width);
	datacharacter(result, height, width);

	printf("\n\n4-defenses Filter");
	datacpy(source, result, height, width);
	averageFiltering_4defenses(source, result, height, width);
//	print(result, height, width);
	datacharacter(result, height, width);

	printf("\n\n8-defenses Filter");
	datacpy(source, result, height, width);
	averageFiltering_8defenses(source, result, height, width);
//	print(result, height, width);
	datacharacter(result, height, width);

	while (1);
}

void datacpy(BYTE *src, BYTE *dst, int height, int width) {
	for (int i = 0; i < height*width; i++)
		*dst++ = *src++;
}

void print(BYTE *src, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%4d", *src++);
		}
		printf("\n");
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
			printf("\n%d", i);
			for (int j = 0; j < graph[i]; j++)
				printf("*");
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

void averageFiltering_line(BYTE *src, BYTE *dst, int height, int width) {
	int x = 1, y, weight;
	for (y = 0; y < height; y++) {
		for(x = 1; x < width-1; x++) {
			filter1[0] = src[y*width + x-1];
			filter1[1] = src[y*width + x];
			filter1[2] = src[y*width + x+1];
			weight = (filter1[0] + filter1[2]) / 2 - filter1[1] ? (filter1[0] + filter1[2]) / 2 - filter1[1] : -(filter1[0] + filter1[2]) / 2 + filter1[1];
			if(weight < 50)
				dst[y*width + x] = (filter1[0] + filter1[2]) / 2;
//			dst[y*height + x] = (src[EAST(x,y,width)] + src[WEST(x,y,width)]) / 2;
			
		}
	}
}
void averageFiltering_4defenses(BYTE *src, BYTE *dst, int height, int width) {
	int x , y;

	for (y = 1; y < height-1; y++) {
		for (x = 1; x < width - 1; x++) {
			dst[y*width + x] = (src[WEST(x,y,width)]+src[EAST(x,y,width)]+src[SOUTH(x,y,width)]+src[NORTH(x,y,width)])/4;
		}
	}
}

void averageFiltering_8defenses(BYTE *src, BYTE *dst, int height, int width) {
	int x, y;
	for (y = 1; y < height - 1; y++) {
		for (x = 1; x < width - 1; x++) {
			dst[y*width + x] = (2 * src[WEST(x, y, width)] + 2*src[EAST(x, y, width)] + 2*src[SOUTH(x, y, width)] + 2*src[NORTH(x, y, width)] + 
				src[NORTHEAST(x, y, width)] + src[SOUTHEAST(x, y, width)] + src[SOUTHWEST(x, y, width)] + src[NORTHWEST(x, y, width)]) / 12;
		}
	}
}