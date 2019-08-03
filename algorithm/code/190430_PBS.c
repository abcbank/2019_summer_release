#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define UNSEEN -INT_MAX
#define MAX_NODE 100
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')
#define tail NULL

typedef struct _node {
	int vertex; // 연결되는 노드
	int weight; // 가중치
	struct _node *next;
}node;

typedef struct _path {
	int vertex;
	struct _path *next;
}path;

node *graph[MAX_NODE];   // 그래프
path *p;
int check[MAX_NODE];   // 가중치 저장
int h[MAX_NODE];   // 힙
int parent[MAX_NODE];   // 부모 노드 저장
int nheap = 0;
FILE *fp;   // 파일 읽어올때 사용함

void input_adjlist(node *a[], int *V, int *E);
// 그래프 설정 함수. 해당 코드에선 graph.txt를 받아 쓴다.
// a : graph, V : vertex size, E : edge size
void print_list(node *a[], int V);
// 프린트 출력 함수. 단 모든 값을 NULL까지 밀어버리므로 head를 복사해서 써야됨
// a : graph, V : vertex size
void pq_init();
// heap 초기화 함수
int pq_empty();
// heap 내의 데이터를 비우는 함수
void upheap(int *a, int k);
// up heap : 주어진 index를 기준으로 위로 올라가며 정렬
// a : heap, k : index num
void downheap(int *a, int k);
// down heap : 주아전 index를 기준으로 아래로 내려가며 정렬
// a : heap, k : index num
void insert(int *a, int *N, int v);
// heap에 데이터를 추가함
// a : heap, N : index size, v : weight
void adjust_heap(int h[], int n);
// 모든 index에 대해 down heap을 실행
// h : heap, n : index size
int pq_extract(int *a);
// root의 값을 뺴오는 함수
// a : heap
int pq_update(int h[], int v, int p);
// 1. 새로운 edge의 가중치가 기존 edge의 가중치보다 적을 경우 해당 node에 대한 queue의 edge를 새로운 edge로 바꿈
// 2. 만약 기존에 없던 node에 대한 edge가 있을경우, 해당 edge를 heap에 집어넣는다.
// h : heap, v : vertex num, p : weight
void PFS_adjlist(node *g[], int V);
// PFS알고리즘
// g : graph, V : vertex size
void visit(int i);
void print_heap(int h[]);
void print_cost(int weight[], int index);

void init_path(int v);
void push_path(int srcv, int curv);
void clear_path();
int main() {
	int V, E;

	printf("\nOriginal Graph\n");
	input_adjlist(graph, &V, &E);
	// get graph
	print_list(graph, V);

	init_path(V);

	printf("\nVisit order of Minimum Spanning Tree\n");
	PFS_adjlist(graph, V);
	// algorithm
	for (int i = 1; i < V; i++) {
		printf("\nparent of %c : %c", (char)i + 65, (char)parent[i] + 65);
		// print parent[]
		print_cost(parent, i);
		// get minimum cost of node i
		printf("\n");
	}
	while (1);
}

void input_adjlist(node *g[100], int *V, int *E)
{
	char vertex[3];
	int i, j, w;
	node *t;

	fp = fopen("graph.txt", "r");

	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		g[i] = NULL;
	for (j = 0; j < *E; j++) {
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		t = (node *)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->weight = w;
		t->next = g[i];
		g[i] = t;
		i = name2int(vertex[1]);
		t = (node *)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->weight = w;
		t->next = g[i];
		g[i] = t;
	}
	fclose(fp);
}

void print_list(node *a[], int V) {
	// this function push all pointers of 'a' until NULL, so make same data  
	int i = 0;
	node *x = (node*)malloc(sizeof(node));
	while (i < V) {
		x = a[i];
		if (x) {
			printf("%c\t", i + 65);
			while (x) {
				printf("%2c", x->vertex + 65);
				x = x->next;
			}
			printf("\n");
			i++;
		}
	}
	free(x);
}

void print_heap(int h[]) {
	int i;
	printf("\n");
	for (i = 1; i <= nheap; i++)
		printf("%c:%d ", int2name(h[i]), check[h[i]]);
	// print heap 
	printf("\n");
}


void pq_init() {
	nheap = 0;
	// set node size of heap zero
}

int pq_empty() {
	if (nheap == 0) return 1;
	return 0;
	// if empty : true
	// else : false
}

void adjust_heap(int h[], int n) {
	int k;
	for (k = n / 2; k >= 1; k--)
		downheap(h, k);
	// downheap all nodes except leaf nodes
}

void upheap(int *a, int k) {
	int v;
	v = a[k];
	while (check[h[k / 2]] < check[v] && k / 2>0) {
		// if weight of children of k is smaller than weight of v,
		// ps. weight of unvisited nodes are minus
		a[k] = a[k / 2];
		k = k >> 1;
	}
	a[k] = v;
}

void downheap(int *a, int k) {
	// N : node number of tree
	int i, v;
	v = a[k];
	while (k <= nheap / 2) {
		i = k << 1;
		if (i < nheap&& check[a[i]] < check[a[i + 1]]) i++;
		if (check[v] > check[a[i]]) break;
		a[k] = a[i];
		k = i;

	}
	a[k] = v;
}

int pq_extract(int *a) {
	// get root node and down heap
	int v = a[1];
	a[1] = a[nheap--];
	downheap(a, 1);

	return v;
}

void insert(int *a, int *N, int v)
{
	a[++(*N)] = v;
	upheap(a, *N);
}

int pq_update(int h[], int v, int p)
{
	if (check[v] == UNSEEN) {
		// if node is unseend before
		h[++nheap] = v;
		check[v] = p; // store the weight
		upheap(h, nheap);
		return 1;
		// add new heap
	}
	else {
		if (check[v] < p) {
			// node is seened before and edge has smaller wieght
			check[v] = p;
			adjust_heap(h, nheap);
			// change edge of node
			return 1;

		}
		else
			return 0;
	}
}

void visit(int i) {
	printf("\nvisit %c", i + 65);
}

void PFS_adjlist(node *g[], int V)
{
	int i;
	node *t;
	pq_init();
	for (i = 0; i < V; i++) {
		check[i] = UNSEEN; // set nodes as unseen
		parent[i] = 0; // initialize a tree
	}
	// init check & parent
	for (i = 0; i < V; i++) {
		if (check[i] == UNSEEN){
			parent[i] = -1; // set the root
			check[i] = 0;
		}
		pq_update(h, i, UNSEEN);
		// push i 
		while (!pq_empty()) {
			print_heap(h);
			// print current heap
			i = pq_extract(h);
			// pop root(heap[0]) of heap
			check[i] = -check[i];
			// if check > 0 -> visited node
			// else         -> unvisited node
			visit(i);
			// print current node
			for (t = g[i]; t != NULL; t = t->next)
				// while graph of current node is end
				if (check[t->vertex] < 0)
					// if node of graph is unvisited
					if (pq_update(h, t->vertex, -t->weight - check[i]))
						// false : node of graph is unseened before
						// true : node of graph is seened before
						parent[t->vertex] = i;   // change parent node
		}
	}
}

void print_cost(int parent[], int index) {
	int i = index, result = 0;
	// needs to print index after, so make same data
	path *t = p + index;

	while (i > 0) {
		// while i > 0
		result += check[i];
		// add check(weight) of i at result
		push_path(index, i);
		i = parent[i];
		// change parent(i)
	}
	printf("\n%c까지 가는 가중치의 총합 : %d", (char)index + 65, result);
	printf("\npath : ");
	while (t) {
		printf("  %c", t->vertex + 'A');
		t = t->next;
	}
}
void init_path(int v) {
	int i;
	p = (path*)malloc(sizeof(path)*(v + 1));
	for (i = 1; i <= v; i++) {
		p[i].next = NULL;
		p[i].vertex = 0;
	}
}

void push_path(int srcv, int curv) {
	path *t = (path*)malloc(sizeof(path));
	t->vertex = curv;
	t->next = p[srcv].next;
	p[srcv].next = t;
}

void clear_path() {
	path *u, *v;
	u = p->next;
	v = u->next;

	while (v) {
		free(u);
		u = v;
		v = v->next;
	}
	free(u);
	free(v);
}