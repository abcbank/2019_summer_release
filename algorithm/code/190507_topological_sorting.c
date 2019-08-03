#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODE 20
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')


FILE *fp;
int top;

typedef struct _node {
	int vertex;
	struct _node *next;
}node;

typedef struct _head {
	int count;
	struct _node *next;
}head;

head network[MAX_NODE];
node *G_node[MAX_NODE];

int check[MAX_NODE];
int stack[MAX_NODE];

void visit(int i) {
	printf("%c", i + 65);
}

int graph[MAX_NODE];

int stack_empty()
{
	return (top < 0);
}
void init_stack()
{
	top = -1;
}

int pop()
{
	return stack[top--];
}
void push(int k)
{
	stack[++top] = k;
}



void input_adjlist(node *a[], int *V, int *E) {
	char vertex[3];
	int i, j;
	node *t;
	fp = fopen("graph.txt", "r");
	fscanf(fp, "%d %d", V, E);

	for (i = 0; i < *V; i++)
	{
		a[i] = NULL;
	}

	for (j = 0; j < *E; j++) {
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		t = (node *)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;

	}
	fclose(fp);
}

void print_adjlist(node *a[], int V)
{
	printf("\n");
	node *t;
	for (int i = 0; i < V; i++)
	{
		printf("%c", int2name(i));
		t = a[i];
		for (int j = 0; j < (int)a[i]; j++)
		{
			printf("%2c", int2name(a[i]->vertex));
			a[i] = a[i]->next;
		}
		printf("\n");
	}
}

void set_count_outdegree(head net[], int V)
{
	int i, count;
	node *t;
	for (i = 0; i < V; i++) {
		count = 0;
		for (t = net[i].next; t; t = t->next)
			count++;
		net[i].count = count;
	}
}


void set_count_indegree(head net[], int V)
{
	int i, j;
	int count;
	node *t;
	for (i = 0; i < V; i++) {
		// 모든 vertex들에 대해
		count = 0;
		for (j = 0; j < V; j++)
			// graph 내에 존재하는 모든 edge를 탐색한 후, 해당 dst가 해당 vertex인 edge가 존재할때마다 count값을 증가시킨다.
			for (t = net[j].next; t; t = t->next)
				if (t->vertex == i) count++;
		net[i].count = count;
	}
}

void topsort(head net[], int V) {
	int i, j, k;
	node *ptr;
	init_stack();
	set_count_indegree(net, V);
	// count 설정
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	// count가 0인 지점(start point)을 push
	for (i = 0; i < V; i++) {
		while (!stack_empty()) {
			// 스택이 완전히 빌때까지
			j = pop();
			printf("%2c", int2name(j));

			for (ptr = net[j].next; ptr; ptr = ptr->next) {
				// network.next -> graph 자료 저장 부분.
				k = ptr->vertex;
				net[k].count--;
				if (!net[k].count)
					// 만약 net[k].count가 0이 아니라면 아직 필요한 요소가 부족한 것.
					push(k);

			}
		}
	}
	printf("\n\n");
}

void revtopsort(head net[], int V)
{
	int i, j, k;
	node *ptr;
	init_stack();
	set_count_outdegree(net, V);
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++) {
		if (stack_empty()) return -1;
		else {
			j = pop();
			printf("%c, ", int2name(j)); // -> visit
			for (k = 0; k < V; k++)
				for (ptr = net[k].next; ptr; ptr = ptr->next)
					if (ptr->vertex == j) {
						net[k].count--;
						if (!net[k].count)
							push(k);
					}
		}
	}
}

int main()
{
	int V, E;

	input_adjlist(G_node, &V, &E);
	//print_adjlist(G_node, V);

	for (int k = 0; k < V; k++)
	{
		network[k].next = G_node[k];
	}
	revtopsort(network, V);
	topsort(network, V);
	while (1);
}