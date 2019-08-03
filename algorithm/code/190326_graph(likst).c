#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100
#define push(data) (stack[++index] = data)
#define pop() (stack[index--])
#define is_stack_empty() (index<0)
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')

typedef struct _node {
	int vertex;
	struct _node *next;
}node;

node head[MAX_NODE];
int check[MAX_NODE];

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

void main() {
	int V, E;

	input_adjlist(head, &V, &E);
	print_list(head, V);
	
}