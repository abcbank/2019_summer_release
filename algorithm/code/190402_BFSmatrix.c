#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#define MAX_NODE 100

typedef struct _dnode {
	int key;
	struct _dnode *next;
	struct _dnode *pre;
}node;

node *head;
node *tail;
int check[MAX_NODE];

int name2int(char c) { return c - 48; }
char int2name(int c) { return c + 48; }

void visit(int i) {
	printf("%d 방문 \n", i+1);
	check[i] = 1;
}

int queue_empty() {
	return head->next == tail;
}

void init_queue() {
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->pre = head;
	head->pre = head;
	tail->next = tail;
}

int put(int data) {
	node *t;
	if ((t = (node*)calloc(1, sizeof(node))) == NULL) {
		printf("Out of memory\n\n");
		return -1;
	}
	t->key = data;
	t->next = tail;
	t->pre = tail->pre;
	tail->pre = t;
	t->pre->next = t;

	return 0;
}

int get() {
	node *t;
	int k;
	t = head->next;
	if (t == tail) {
		printf("Queue underflow\n\n");
		return -1;
	}
	k = t->key;
	head->next = t->next;
	t->next->pre = head;
	free(t);
	return k;
}

int **init_map() {
	int **a = (int**)calloc(MAX_NODE, sizeof(int*));
	for (int i = 0; i < MAX_NODE; i++) {
		a[i] = (int*)calloc(MAX_NODE, sizeof(int));
	}
	return a;
}

void input_adjmatrix(int **map, int *V, int *E) {
	int i, j, k;
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
		i = name2int(line[0]) - 1;
		j = name2int(line[1]) - 1;
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
			printf("% 3d", a[i - 1][j]);
		printf("\n");
	}
}

void BFS_adjmatrix(int a[][MAX_NODE], int V) {
	int i, j,k;
	init_queue();
	for (i = 0; i < V; i++) check[i];
	for (i = 0; i < V; i++) {
		if (check[i] == 0)
			put(i);
		while (!queue_empty()) {
			k = get(i);
			visit(i);
			for (j = 0; j < V; j++)
				if (a[i][j] == 1 && check[j] != 1)
					put(j);
		}
	}
}

int main() {
	int V, E;
	int **map = init_map();
	input_adjmatrix(map, &V, &E);
	print_adjmatrix(map, V);
	BFS_adjmatrix(map, V);
	while (1);
}