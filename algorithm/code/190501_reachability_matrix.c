#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100

#define name2int(c) (c-'A')
#define int2name(c) (c+'A')
#define tail NULL



typedef struct _node {
	int vertex;

	struct _node *next;
}node;

int map[MAX_NODE][MAX_NODE];
int check[MAX_NODE];
int stack[MAX_NODE];
int index;

void push(int data) {
	stack[++index] = data;
}

int pop() {
	return stack[index--];
}

int is_stack_empty() { return index < 0; }

void init_stack() {
	index = -1;
}

void visit(int i) {
	printf("%2c 방문 ", i + 'A');
}

void DFS_directed(int a[][MAX_NODE], int V) {
	int i, j, l, k;
	init_stack();
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++)
			check[j] = 0;
		push(i);
		check[i] = 1;
		printf("\n%c : ", int2name(i));
		while (!is_stack_empty(index)) {
			j = pop();
			visit(j);
			for (k = 0; k < V; k++) {
				if (a[j][k] && !check[k]) {
					push(k);
					check[k] = 1;
				}
			}
		}
		printf("\n");
	}
}

void input_adjmatrix(int g[][MAX_NODE], int *V, int *E) {
	char vertex[3];
	int i, j, k;
	FILE *fp;
	fp = fopen("graph.txt", "r");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 0;
	for (i = 0; i < *V; i++)
		g[i][i] = 0;
	for (k = 0; k < *E; k++) {
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = 1;
	}
	fclose(fp);
}

void warshall(int a[][MAX_NODE], int V) {
	int x, y, k;
	for (x = 0; x < V; x++)
		for (y = 0; y < V; y++) {
			if (map[y][x])
				for (k = 0; k < V; k++) {
					if (map[x][k])
						map[y][k] = 1;
				}
		}
}

void print_map(int a[][MAX_NODE], int V) {
	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			printf("%2d", a[i][j]);
		}
		printf("\n");
	}
}

void main() {
	int V, E;
	input_adjmatrix(map, &V, &E);
	print_map(map, V);
	printf("\n\n");
	DFS_directed(map, V);
	for (int i = 0; i < V; i++)
		map[i][i] = 1;
	warshall(map,V);
	print_map(map, V);
	while (1);
}