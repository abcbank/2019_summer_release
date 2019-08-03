#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define SRC 'S'
#define SINK 'T'
#define MAX_NODE 100

// residual : residual 그래프 저장
// capacity : 본래 그래프 저장
// flow : capacity -> residual의 오차값을 저장

int capacity[MAX_NODE][MAX_NODE]; // for capacity
int flow[MAX_NODE][MAX_NODE]; // for flow
int residual[MAX_NODE][MAX_NODE]; // for residual network
int check[MAX_NODE]; // for checking the visit
int parent[MAX_NODE]; // for bfs-based tree
int path[MAX_NODE];	// for augmenting path
int queue[MAX_NODE];
int front;
int rear;

//-------------name <-> integer---------------------
// 단, 예전에 쓰던 애들하곤 좀 다름

int name2int(char c) {
	if (c == SRC) return 0;
	if (c == SINK) return 1;
	return c - 'A' + 2;
}

int int2name(int i) {
	if (i == 0)return SRC;
	if (i == 1) return SINK;
	return i + 'A' + 2;
}

//---------------------------------------------------


//----------- queue ------------

void init_queue() {
	front = rear = 0;
}

int queue_empty() {
	if (front == rear)
		return 1;
	return 0;
}

void put(int k) {
	queue[rear] = k;
	rear = ++rear%MAX_NODE;
}

int get() {
	int i;
	i = queue[front];
	front = ++front % MAX_NODE;
	return i;
}

//------------------------------

//--------------------------- path --------------------------------

int get_augment_path(int a[][MAX_NODE], int V, char src, char dst);
void reverse_path();

//-----------------------------------------------------------------

//----------------------------------- construct ----------------------------------------

void construct_residual(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V);

//--------------------------------------------------------------------------------------

//------------------------------------------ API -----------------------------------------------

void network_flow(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V, int src, int dst);

//----------------------------------------------------------------------------------------------

//--------------------------- matrix 관련 -------------------------------

int clear_matrix(int x[][MAX_NODE], int V) {
	int i, j;
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			x[i][j] = 0;
}

void adjmatrix(int map[][MAX_NODE], int *V, int *E) {
	int i, j, k, weight;
	char line[3];
	FILE *fp;

	fp = fopen("graph.txt", "r");
	fscanf(fp, "%d %d", V, E);
	clear_matrix(map, *V);

	for (k = 0; k < *E; k++) {
		fscanf(fp, "%s %d", line, &weight);
		i = name2int(line[0]);
		j = name2int(line[1]);
		map[i][j] = weight;
	}
}

void print_matrix(int map[][MAX_NODE], int V) {
	int i, j;
	printf(" ");
	for (i = 0; i < V; i++)
		printf("%4c", int2name(i));
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("%c", int2name(i));
		for (j = 0; j < V; j++)
			printf("%4d", map[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

//-----------------------------------------------------------------------

int main() {
	int V, E;
	adjmatrix(capacity, &V, &E);
	
	network_flow(capacity, flow, residual, V, SRC, SINK);
	printf("Residual Matrix\n");
	print_matrix(residual, V);
	printf("Flow Matrix\n");
	print_matrix(flow, V);
}

//--------------------------- path --------------------------------

int get_augment_path(int a[][MAX_NODE], int V, char src, char dst) {
	int i, j;
	init_queue();

	for (i = 0; i < V; i++) {
		check[i] = 0;
		parent[i] = -1;
	}

	i = name2int(src);

	//if(!check[i]) -> always true
	put(i);
	check[i] = 1;

	while (!queue_empty()) {
		i = get();
		if (i == name2int(dst)) break;
		
		for (j = 0; j < V; j++) {
			if(a[i][j] != 0)
				if (!check[j]) {
					put(j);
					check[j] = 1;
					parent[j] = i;
				}
		}
	}

	reverse_path();

	if (i == name2int(dst)) return 1;
	else return 0;
}

void reverse_path() {
	int count = 0, i;
	int *tmp = (int*)malloc(sizeof(int)*MAX_NODE);

	i = name2int(SINK);
	while (i >= 0) {
		tmp[count] = i;
		i = parent[i];
		count++;
	}

	for (i = 0; i < count; i++)
		path[i] = tmp[count - i - 1];
	path[i] = -1;
	free(tmp);
}

//-----------------------------------------------------------------

//----------------------------------- construct ----------------------------------------

void construct_residual(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V) {
	int i, j;
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			r[i][j] = c[i][j] - f[i][j];
}

//--------------------------------------------------------------------------------------

//------------------------------------------ API -----------------------------------------------

void network_flow(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V, int src, int dst) {
	int i, min;
	
	clear_matrix(f, V);
	clear_matrix(r, V);
	construct_residual(c, f, r, V);

	while (get_augment_path(r, V, src, dst)) {
		min = INT_MAX;
		for (i = 1; path[i] >= 0; i++)
			min = min < r[path[i - 1]][path[i]] ? min : r[path[i - 1]][path[i]];
		for (i = 1; path[i] >= 0; i++) {
			f[path[i - 1]][path[i]] = f[path[i - 1]][path[i]] - min;
			f[path[i]][path[i - 1]] = -f[path[i - 1]][path[i]];
		}
		construct_residual(c, f, r, V);
	}
}

//----------------------------------------------------------------------------------------------
