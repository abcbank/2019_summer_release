#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100
#define push(data) (stack[++index] = data)
#define pop() (stack[index--])
#define is_stack_empty() (index<0)
#define name2int(c) (c-48)
#define int2name(c) (c+48)
#define tail NULL



typedef struct _node {
	int vertex;
	
	struct _node *next;
}node;

node head[MAX_NODE];
int check[MAX_NODE];
int stack[MAX_NODE];
int index;

void init_stack() {
	index = -1;
}

void visit(int i) {
	printf("%d 방문 \n", i);
}

void nrDFS_adjlist(node *a[], int V)
{
	node *t;
	int i;
	init_stack();
	for (i = 0; i < V; i++)
		check[i] = 0;

	for (i = 0; i < V; i++)
	{
		if (check[i] == 0)
		{
			push(i);
			check[i] = 1;
			while (!is_stack_empty())
			{
				i = pop();
				visit(i);
				for (t = a[i]; t != NULL; t = t->next)
						if (check[t->vertex] == 0)
						{
							push(t->vertex);
							check[t->vertex] = 1;
						}
			}
		}
	}
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
	node *t;
	for (i = 0; i < V; i++) {
		t = a[i];
		if (t != NULL) {
			printf("%d\t", i);
			while (t) {
				printf("%2d", t->vertex);
				t = t->next;
			}
			printf("\n");
		}
	}
}

void main() {
	int V, E;
	input_adjlist(head, &V, &E);
	print_list(head, V);
	nrDFS_adjlist(head, V);
	for (int i = 0; i < V; i++)
		printf("%2d", check[i]);
	while (1);
}