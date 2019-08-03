#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100
#define MAX_WEIGHT 1000
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')

int map[MAX_NODE][MAX_NODE];

void init_map(int V){
    int i,j;
    for(i = 0; i < V; i++)
        for(j = 0; j < V; j++)
            map[i][j] = MAX_WEIGHT;
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

void input_adjmatrix(int g[][MAX_NODE], int *V, int *E) {
	char vertex[3];
	int i, j, k;
	int weight;
	FILE *fp;
	fp = fopen("graph.txt", "r");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 0;
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
}