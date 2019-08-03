#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')
#define tail NULL



typedef struct _node {
	int vertex;
	struct _node *next;
}node;

node head[MAX_NODE];
int check[MAX_NODE];
int son_of_root;
int order;

int AP_recur(node *a[], int i) {
	node *t;
	int min, m;

	check[i] = min = ++order;
	for (t = a[i]; t != tail; t = t->next) {
		if (i == 0 && check[t->vertex] == 0)
			son_of_root++;
		if (check[t->vertex] == 0) {
			m = AP_recur(a, t->vertex);
			if (m < min) min = m;
			if(m >= check[i] && i != 0)
				printf("* %c % 2d : %d\n", int2name(i),check[i], m);
			else
				printf("  %c % 2d : %d\n", int2name(i),check[i], m);	
		}
		else
			if (check[t->vertex] < min)
				min = check[t->vertex];
	}
	return min;
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

void AP_search(node *a[], int V) {
	int i = 0;

	for (i = 0; i < V; i++)
		check[i] = 0;
	order = son_of_root = 0;
	AP_recur(a, 0);
}

void print_list(node *a[], int V) {
	int i;
	node *t;
	for (i = 0; i < V; i++) {
		t = a[i];
		if (t != NULL) {
			printf("%c\t", int2name(i));
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
	node **p = head;	
	order = 0;
	son_of_root = 0;

	input_adjlist(head, &V, &E);
	print_list(p, V);
//	for (int i = 0; i < V; i++)
//		printf("%2d", check[i]);
	AP_search(head, V);
	while (1);

}