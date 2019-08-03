#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100
#define push(data) (stack[++index] = data)
#define pop() (stack[index--])
#define is_stack_empty() (index<0)
#define name2int(c) (c-48)
#define int2name(c) (c+48)

typedef struct _node {
	int vertex;
	struct _node *next;
}node;


typedef struct _dnode {
	int key;
	struct _dnode *next;
	struct _dnode *pre;
}qnode;

qnode *qhead;
qnode *qtail;
node head[MAX_NODE];
int check[MAX_NODE];

int queue_empty() {
	return qhead->next == qtail;
}

void visit(int i) {
	printf("%d 방문 \n", i + 1);
	check[i] = 1;
}

void init_queue() {
	qhead = (qnode*)calloc(1, sizeof(qnode));
	qtail = (qnode*)calloc(1, sizeof(qnode));
	qhead->next = qtail;
	qtail->pre = qhead;
	qhead->pre = qhead;
	qtail->next = qtail;
}

void put(int data) {
	qnode *t;
	if ((t = (qnode*)calloc(1, sizeof(qnode))) == NULL) {
		printf("Out of memory\n\n");
		return -1;
	}
	t->key = data;
	t->next = qtail;
	t->pre = qtail->pre;
	qtail->pre = t;
	t->pre->next = t;

	return 0;
}

int get() {
	qnode *t;
	int k;
	t = qhead->next;
	if (t == qtail) {
		printf("Queue underflow\n\n");
		return -1;
	}
	k = t->key;
	qhead->next = t->next;
	t->next->pre = qhead;
	free(t);
	return k;
}

void input_adjlist(node *a[], int *V, int *E) {
	char vertex[3];
	int i, j;
	node *t;
	printf("\nInput number of node & edge\n");
	scanf("%d %d", V, E);
	for (j = 0; j < *E; j++) {
		printf("\nInput two node consist of edge →");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		t = (node *)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
		i = name2int(vertex[1]);
		t = (node *)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}
}

void print_list(node *a[], int V) {
	int i;
	for (i = 0; i < V; i++) {
		if (a[i] != NULL) {
			printf("%d\t", i);
			while (a[i]) {
				printf("%2d", a[i]->vertex);
				a[i] = a[i]->next;
			}
			printf("\n");
		}
	}
}

void BFS_adjmatrix(int *a[], int V) {
	int i, j, k;
	node *t;
	init_queue();
	for (i = 0; i < V; i++) check[i];
	for (i = 0; i < V; i++) {
		if (check[i] == 0)
			put(i);
		while (!queue_empty()) {
			k = get(i);
			t = a[k];
			visit(k);
			while (t) {
				if (check[t->vertex] != 1) {
					put(t->vertex);
					check[t->vertex] = 1;
				}
				t = t->next;
				
			}
		}
	}
}

void main() {
	int V, E;

	input_adjlist(head, &V, &E);
//	print_list(head, V);
	BFS_adjmatrix(head, V);
}