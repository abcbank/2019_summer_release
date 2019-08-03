#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Node {
	int data;
	struct Node *next;
}node;

node *init_Node_C(int data) {
	node *a=(node*)malloc(sizeof(node));
	a->data = data;
	a->next = NULL;
	return a;
}

void insert_node(node *p,node *n) {
	p->next = n;
}
int main(void) {
	node root;
	node *pre,*pr = &(root);
	int del;
	
	root.data = 0;
	root.next = NULL;

	srand((unsigned int)time(NULL));

	for(int i = 1; i < 10; i++) {
		node *new_node = init_Node_C(i);
		pr->next = new_node;
		pr = pr->next;
	}
	del = rand() % 9+1;
	
	printf("data가 %d인 node 삭제\n", del);

	pr = &root;
	while (pr->next) {
		if (pr->next->data == del) {
			pre = pr->next;
			pr->next = pr->next->next;
			free(pre);
			pr = pr->next;
		}
		else {
			pr = pr->next;
		}
	}
	del = rand() % 9+1;
	
	printf("data가 %d인 node 삭제\n", del);

	pr = root.next;
	pre = &root;
	// 현재 위치를 삭제할땐 이전 노드를 저장하는 포인터가 하나 더 필요
	while (pr) {
		if (pr->data == del) {
			pre->next = pr->next;
			free(pr);
			pr = pre->next;
		}
		else {
			pre = pre->next;
			pr = pr->next;
		}
	}
	pr = &root;
	while (pr) {
		printf("%d번째 노드 참조\n", pr->data);
		pr = pr->next;
	}
	while (1);
}