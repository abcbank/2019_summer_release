#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define INFINITE 1000
#define start_point 6
#define name2int(n) (n-'A')
#define int2name(n) (n+'A')

int **map;
//int **path;
int *check;
int *parent;
int *distance;

void adj_map(int *v, int *e);
void print_map(int v);
void dijkstra(int s, int V);

int main() {
	int V, E;
	adj_map(&V, &E);
	print_map(V);

	check = (int*)calloc(V , sizeof(int));
	parent = (int*)calloc(V , sizeof(int));
//	path = (int**)malloc(V * sizeof(int));

	dijkstra(start_point, V);
}

void adj_map(int *v, int *e) {
	int i, j, k, w;
	char vertex[3];
	FILE *fp;

	fp = fopen("graph.txt", "r");
	fscanf(fp, "%d %d", v, e);
	map = (int**)malloc(*v * sizeof(int*));
	for (i = 0; i < *v; i++) {
		map[i] = (int*)malloc(*v * sizeof(int));
	}

	for (i = 0; i < *v; i++)
		for (j = 0; j < *v; j++)
			map[i][j] = (j == i) ? 0 : INFINITE;
	for (k = 0; k < *e; k++) {
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		map[i][j] = w;
		map[j][i] = w;
	}
	fclose(fp);
}

void print_map(int v) {
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++)
			printf("%4d", map[i][j]);
		printf("\n");
	}
}

void dijkstra(int s, int V) {
	int x, y, i, d;
	int checked = 0;
	
	for (i = 0; i < V; i++) {
		distance[i] = map[s][i];
		// 시작 vertex에 관련된 거리 정보를 가져온다.
		if (i != s)
			parent[i] = s;
			// 따로 골라내기 귀찮아서 그냥 s로 통일. 이후 distance 내의 값을 통해 연결되어있는지 아닌지 확인한다.
	}
		
	check[s] = 1;
	// 시작 지점은 이미 방문했다 가정한다.
	checked++;
	// 방문한 vertex 개수 

	while (checked == V) {
		// 방문한 vertex가 V개가 될때까지
		x = 0;
		for (i = 0; i < V; i++)
			if (check[i] == 0 && distance[i] < distance[x]) x = i;
			// 최단 거리를 탐색
		check[x] = 1;
		// 해당 노드를 방문
		checked++;
		// 방문한 node수 하나 추가
		
		for (y = 0; y < V; y++) {
		// x 좌표 기준으로 거리를 재정렬한다.
			if (y == x || check[y] || map[x][y] == INFINITE)
			// y == x -> 거리가 0, check[y] == TRUE -> 이미 방문한 노드이기 때문에 굳이 거리를 재정렬할 필요 없음
			// map[x][y] == INFINITE -> 연결되지 않은 node이므로 굳이 탐색할 필요 없음
				continue;
				// 위의 세가지 경우를 제외해준다.
			d = distance[x] + map[x][y];
			// 만약 세가지 경우가 아닐때, 시작 node에서 x를 경유해 y까지 가는 거리는 ((x까지의 거리) + map[x][y])가 된다.
			if (d < distance[y]) {
				// 기존 y까지의 거리보다 새로 탐색한 거리가 더 가깝다면
				distance[y] = d;
				parent[y] = x;
				// 바꿔줌
			}
		}
	}
}