#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX_NODE 100
#define MAX_SIZE 10000
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')

typedef struct _node {
	int vertex;
	struct _node *next;
}node;

node *graph[MAX_NODE];
int stack[ MAX_SIZE ];
int check[MAX_NODE];
int order;
int top;

// stack function
void push(int data) {
	stack[++top] = data;
}

int pop() {
	return stack[top--];
}

int stack_empty() {
	return top == -1;
}

void init_stack() {
	top = -1;
}
// end stack function

int strong_recur(node *g[], int i)
{
	// m : 하위 node 중 가장 작은 방문순서
	// min : 본인 포함한 하위 node 중 가장 작은 방문 순서
	// flag : mode
	// k : circular check할때 pop을 받아오는 매개변수
	int m, min, k, flag;
	node *t;
	check[i] = min = ++order;
	// 방문 순서를 ++order로 설정. 
	push(i);
	// node 번호를 stack에 저장해둔다.
	for (t = g[i]; t != NULL; t = t->next) {
		if (check[t->vertex] == 0)
			m = strong_recur(g,t->vertex);
			// 자식 node들 중 방문하지 않은 node가 있다면 재귀함수 호출
			// DFS형식으로 방문하는 동시에, 방문한 vertex를 stack에 저장
		else
			m = check[t->vertex];
			// 자식 node들 중 이미 방문한 node가 있다면 해당 node의 값을 가져온다 -> 이미 방문한 node는 항상 현재 node보다 방문 순서가 작다는 점을 주의하자.
		min = min < m ? min : m;
		// min과 m 중 더 작은 값을 가져옴
	}
	if (min == check[i]) { // check for cycle, 각 그래프의 끝마다 실행한다. 
		flag = 0;
		while ((k = pop()) != i) {
		// while문 내부가 돌지 않더라도 이 구문은 실행된다. -> 따라서 pop 구문은 실행됨
		// pop값과 i 값이 다르다 -> 해당 node를 통해 다른 node로 이동할 수 있는 node
		// pop값과 i 값이 같다 -> 해당 node를 통해 다른 node로 이동할 수 없는 leaf node
		// pop -> graph 내에서 해당 node를 지워버리는 것과 같다고 생각하면 됨.
			printf("%c ", int2name(k));
			// 출력 -> 서로 다르다면 loop를 형성하는 것이다.
			check[k] = MAX_NODE + 1;
			// loop를 형성하는 node들은 check 값을 바꿔준다.
			flag = 1;
			// 하나라도 출력했다면 mode를 바꿔줌
			// flag == 0 -> loop 없음, flag == 1 -> loop 존재
		}
		if (flag) printf("%c\n", int2name(k));
		// 만약 loop가 존재한다면, 현재 node 또한 출력한다.
	}
	return min;
}

void input_adjlist(node *a[], int *V, int *E) {
	char vertex[3];
	int i, j;
	node *t;
	FILE *fp;
	fp = fopen("graph.txt", "r");
	fscanf(fp, "%d %d", V, E);
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

void print_list(node *a[], int V) {
	int i;
	for (i = 0; i < V; i++) {
		if (a[i] != NULL) {
			printf("%c\t", int2name(i));
			while (a[i]) {
				printf("%2c",int2name(a[i]->vertex));
				a[i] = a[i]->next;
			}
			printf("\n");
		}
	}
}

void strong(node *g[], int V) {
	order = 0;
	init_stack();
	for (int i = 0; i < V; i++)
		check[i] = 0;
	for (int i = 0; i < V; i++)
		if(check[i] == 0)
			strong_recur(g, i);
}

int main() {
	int V, E;
	input_adjlist(graph, &V, &E);
	strong(graph, V);
}