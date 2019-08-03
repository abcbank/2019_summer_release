#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100
#define MAX_WEIGHT 1000
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

void init_map(int V) {
	int i, j;
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			map[i][j] = MAX_WEIGHT;
}

void print_map(int a[][MAX_NODE], int V) {
	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			if (a[i][j] == MAX_WEIGHT)
				printf("   *");
			else printf("%4d", a[i][j]);
		}
		printf("\n");
	}
}

void floyd(int a[][MAX_NODE], int V){
int x, y, k;
for (y = 0; y < V; y++)
	for (x = 0; x < V; x++)
		for (k = 0; k < V; k++)
			if (a[x][y] + a[y][k] < a[x][k])
				a[x][k] = a[x][y] + a[y][k];
}

void input_adjmatrix(int g[][MAX_NODE], int *V, int *E) {
	char vertex[3];
	int i, j, k;
	int weight;
	FILE *fp;
	fp = fopen("graph.txt", "r");
	fscanf(fp, "%d %d", V, E);
	init_map(*V);
	for (i = 0; i < *V; i++)
		g[i][i] = 0;
	for (k = 0; k < *E; k++) {
		fscanf(fp, "%s %d", vertex, &weight);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = weight;
	}
	fclose(fp);
}

void main() {
	int V, E;
	input_adjmatrix(map, &V, &E);
	print_map(map, V);
	printf("\nFloyd Algorithm!!\n\n");
	floyd(map, V);
	print_map(map, V);
	while (1);
}