#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#define MAX_NODE 100
int name2int(char c) { return c - 48; }
char int2name(int c) { return c + 48; }

int **init_map() {
	int **a = (int**)calloc(MAX_NODE, sizeof(int*));
	for (int i = 0; i < MAX_NODE; i++) {
		a[i] = (int*)calloc(MAX_NODE, sizeof(int));
	}
	return a;
}

void input_adjmatrix(int **map, int *V, int *E) {
	int i, j,k;
	char line[3];
	printf("num of vertex : ");
	scanf_s("%d", V);
	printf("num of Edges : ");
	scanf_s("%d", E);
	for (i = 0; i < *V; i++) 
		map[i][i] = 1;
	for (k = 0; k < *E; k++) {
		printf("\nInput two node consist of edge : ");
		scanf("%s", line);
		i = name2int(line[0])-1;
		j = name2int(line[1])-1;
		map[i][j] = 1;
		map[j][i] = 1;
	}
}
void print_adjmatrix(int **a, int V)
{
	int i, j;
	for (i = 0; i <= V; i++)
		printf("% 3c", int2name(i));
	printf("\n");
		for (i = 1; i <= V; i++) {
			printf("% 3c", int2name(i));
			for (j = 0; j < V; j++)
				printf("% 3d", a[i-1][j]);
			printf("\n");
		}
}

int main() {
	int V,E;
	int **map = init_map();
	input_adjmatrix(map, &V, &E);
	print_adjmatrix(map, V);
	while (1);
}