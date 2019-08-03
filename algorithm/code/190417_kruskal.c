#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define UNSEEN -INT_MAX
#define MAX_NODE 50
#define MAX_EDGE 100
#define ONLY_FIND 0
#define UNION 1
#define tail NULL
#define name2int(c) (c - 'A')
#define int2name(c) (c + 'A')

typedef struct edge {
	int v1, v2;
	int weight;
}edge;

int parent[MAX_NODE]; // tree structure for representing the set
int height[MAX_NODE]; // store the height of the tree
int cost = 0;
int nheap = 0; // # of elements in the heap
int h[MAX_NODE];
edge *Edge;
FILE *fp;
void visit(int e);
void input_edge(int *V, int *E);
// get edge imformation in graph.txt
void kruskal(int V, int E);
// kruskal algorithm
void pq_insert(int v);
// insert leaf edge
int pq_extract();
// extract root
void find_init(int vertex_size) {
	int i;
	for (i = 0; i < vertex_size; i++)
		parent[i] = -1;
}
// init find
void pq_init() { nheap = 0; }
// init heap
void visit(int e);
// visit algorithm
int pq_empty() {
	if (nheap == 0) return 1;
	return 0;
}
// heap 내의 데이터를 비우는 함수
void upheap(int k);
void downheap(int k);
int find_set(int elem, int asso, int flag);
void union_set(int elem, int asso);

void main()
{
	int V, E;
	fp = fopen("graph.txt", "rt");
	input_edge(&V, &E);
	printf("\n\nVisited edge of minimum spanning tree\n");
	kruskal(V, E);
	printf("\n\nMinimum cost is \n %d\n", cost);
	fclose(fp);
	while (1);
}

void input_edge(int *V, int *E) {
	char vertex[3];
	int i, w;
	printf("\nInput number of nodes and edges\n");
	fscanf(fp, "%d %d", V, E);
	Edge = (edge*)malloc(sizeof(edge)*(*E));
	for (i = 0; i < *E; i++) {
		printf("\nInput two nodes consisting of edge and its weight →");
		fscanf(fp, "%s %d", vertex, &w);
		vertex[2] = NULL;
		Edge[i].v1 = name2int(vertex[0]);
		Edge[i].v2 = name2int(vertex[1]);
		Edge[i].weight = w;
	}
}

int find_set(int elem, int asso, int flag) {
	int i = elem, j = asso;
	while (parent[i] >= 0)
		i = parent[i];
	while (parent[j] >= 0)
		j = parent[j];
	if ((flag == UNION) && (i != j))
		union_set(i, j);
	return (i != j);
}

void kruskal(int V, int E) {
	int n, val = 0;
	find_init(V);
	pq_init();
	for (n = 0; n < E; n++)
		pq_insert(n);
	// weight에 따라 edge[0] ~ edge[E-1]까지 힙정렬
	n = 0;
	while (!pq_empty()) {
		// 힙이 빌때까지
		val = pq_extract();
		// get
		if (find_set(Edge[val].v1, Edge[val].v2, UNION)) {
			visit(val);
				n++;
		}
		if (n == V - 1)
			break;
	}
}

void union_set(int elem, int asso) {
	parent[elem] = asso;
	printf("\tcombine!!\t");
}

void pq_insert(int v) {
	h[++(nheap)] = v;
	upheap(nheap);
}

int pq_extract() {
	// get root node and down heap
	int v = h[1];
	h[1] = h[nheap--];
	downheap(1);

	return v;
}

void upheap(int k) {
	int v;
	v = h[k];
	while (Edge[h[k / 2]].weight >= Edge[v].weight && k / 2>0) {
		// if weight of children of k is smaller than weight of v,
		// ps. weight of unvisited nodes are minus
		h[k] = h[k / 2];
		k = k >> 1;
	}
	h[k] = v;
}

void downheap(int k) {
	// N : node number of tree
	int i, v;
	v = h[k];
	while (k <= nheap / 2) {
		i = k << 1;
		if (i < nheap&& Edge[h[i]].weight > Edge[h[i + 1]].weight) i++;
		if (Edge[v].weight <= Edge[h[i]].weight) break;
		h[k] = h[i];
		k = i;
	}
	h[k] = v;
}

void visit(int e) {
	printf("%c%c ", int2name(Edge[e].v1),
		int2name(Edge[e].v2));
	cost += Edge[e].weight;
}
