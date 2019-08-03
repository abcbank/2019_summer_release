// 처음과 마지막줄만 특정 dir에 대해 shift를 세번 수행한다.

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

#define SIZE 15
#define IN_STACK -1
#define BACKGROUND 0
#define COLORED 1
#define NORTH 1
#define NORTHEAST 2
#define EAST 4
#define SOUTHEAST 8
#define SOUTH 16
#define SOUTHWEST 32
#define WEST 64
#define NORTHWEST 128
#define tail NULL
#define BYTE unsigned char 

typedef struct _node {
	int x;
	int y;
	BYTE dir;
}node;

int bitmap[SIZE*SIZE] = { 
0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,
0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,
0,1,0,0,0,0,1,0,0,0,1,1,0,1,0,
0,1,0,1,1,0,1,0,1,1,1,0,0,1,0,
0,1,0,0,1,0,1,0,1,0,0,0,0,1,0,
0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,
0,0,0,1,1,0,1,0,1,0,1,1,0,1,0,
0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,
0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,
0,1,1,1,1,1,0,1,0,0,1,1,0,1,0,
0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,
0,1,1,1,0,1,0,1,0,0,0,0,0,1,0,
0,1,0,0,0,1,0,1,1,1,1,1,1,1,0,
0,1,1,1,1,1,0,0,0,0,0,0,0,0,0
};
//int *bitmap;
BYTE color = 48;
int stack[SIZE*SIZE];
int top;

node* new_node(int i, int j) {
	node *t = (node*)malloc(sizeof(node));
	t->x = j;
	t->y = i;
	t->dir = NORTH;
	return t;
}

void init_stack(void);
void CCA();
void DFS(int i, int j);
void push(node *pre);
void change_color(node* crd);
node* pop();
int stack_empty();
void print_bitmap() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%c", bitmap[i*SIZE+j]);	
		}
	printf("\n");
	}
}


int main(void) {
	LARGE_INTEGER freq, start, stop;
	double diff;
	srand((unsigned int)time(NULL));
	// bitmap = (int*)malloc(sizeof(int) * 400);
	// for (int i = 0; i < SIZE*SIZE; i++)
	// 	bitmap[i] = rand() % 2;
	printf("Back Ground(0) : \"%c\", Line(1) : \"%c\" \n",BACKGROUND, COLORED);
	printf("Color of Line is reference order\n\n");
	printf("Provided Bitmap ! \n\n");
	print_bitmap();

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point
	
	CCA();
	
	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	
	printf("\nResult ! \n\n");
	print_bitmap();

	printf("\ntime : %f\n", diff);

	while (1);
}

int bitmap_coord(int i, int j, BYTE dir) {
		switch (dir) {
		case NORTH:
			 return (i - 1)*SIZE + j;
			break;
		case NORTHEAST:
			 return (i - 1)*SIZE + j + 1;
			break;
		case EAST:
			 return i * SIZE + j + 1;
			break;
		case SOUTHEAST:
			 return (i + 1)*SIZE + j + 1;
			break;
		case SOUTH:
			 return (i + 1)*SIZE + j;
			break;
		case SOUTHWEST:
			 return (i + 1)*SIZE + j - 1;
			break;
		case WEST:
			return i * SIZE + j - 1;
			break;
		case NORTHWEST:
			return (i - 1)*SIZE + j - 1;
			break;
		default:
			printf("\nERROR\n");
		}
	
		return -1;
}
void init_stack() {
	top = -1;
}

int stack_empty() {
	return top < 0;
}

void push(node *pre) {
	stack[++top] = (int)pre;
}

node* pop() {
	return (node*)(stack[top--]);
}

void CCA() {
	int i, j;
	for (i = 0; i < SIZE; i++) 
		for (j = 0; j < SIZE; j++) 
			if (bitmap[i*SIZE+j] == 1)
				DFS(i, j);
}

void change_color(node* cur) {
	bitmap[cur->y*SIZE+cur->x] = color;
}


void DFS(int i, int j) {
	int coord, x, y;
	node *push_node, *cur;
	node *head = new_node(i,j);

	init_stack();
	push(head);

	color++;

	while (!stack_empty()) {
		 cur = pop();
		 change_color(cur);
		while (cur->dir > 0) {
			coord = bitmap_coord(cur->y, cur->x, cur->dir); 
			if (bitmap[coord] == COLORED) {
				push_node = (node*)malloc(sizeof(node));
				push_node->dir = NORTH;
				push_node->x = coord % SIZE;
				push_node->y = coord / SIZE;
				push(cur);
				push(push_node);
				break;
			}
			if ((cur->dir == SOUTH && cur->x == 0) || (cur->dir == NORTH && cur->x == SIZE - 1))
				cur->dir = cur->dir << 4;
			else
				cur->dir = cur->dir << 1;
		}
	}
}