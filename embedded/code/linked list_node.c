#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100
#define name2int(c) (c-48);


typedef struct _node {
	int vertex;
	struct _node *next;
}node;

void input_adjlist(node *a[], int *V, int *E) {
	char line[3];
	int i, j;
	node *t;
	printf("number of vertex : ");
	scanf("%d", V);

	printf("number of edge : ");
	scanf("%d", E);

	for (j = 0; j < *E; j++) {
		printf("\nInput two node consist of edge →");
		scanf("%s", line);
		t = (node *)malloc(sizeof(node));
		i = name2int(line[0]);
		t->vertex = name2int(line[1]);
		t->next = *a+i;
		a[i] = t;
		i = name2int(line[1]);
		t = (node *)malloc(sizeof(node));
		t->vertex = name2int(line[0]);
		t->next = NULL;
		t->next = *a+i;
		a[i] = t;


	}
}

void print_list(node *a[], int V) {
	int i = 0;
	node *tmp;
	while (i < V) {
		printf("%d", i);
		if (a[i]->vertex!=-1) {
			tmp = &a[i];
			while (a[i]->vertex == -1) {
				printf("%2d", tmp->vertex);
				tmp = tmp->next;
			}
		}
		i++;
	}
}

int main(void) {
	node a[MAX_NODE];
	int i, V, E;

	for (i = 0; i < 5; i++) {
		a[i].next = NULL;
		a[i].vertex = -1;
	}

	input_adjlist(&a, &V, &E);
	print_list(&a, V);

}