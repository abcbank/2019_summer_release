#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
}node;

node * init_Node_A() {
	node *a = (node*)malloc(sizeof(node));
	a->data = 0;
	a->next = NULL;
	return a;
}

node init_Node_B() {
	node a;
	a.data = 0;
	a.next = NULL;
	printf("A : %p\n", &a);
	return a;
}

void init_Node_C(node **a) {
	(*a)->data = 0;
	(*a)->next = NULL;
	printf("C : %p\n", a);
}

int main(void) {
	node a;
	node *b = init_Node_A();
	node *c = (node*)malloc(sizeof(node));
	printf("init A : 리턴 - node 포인터, 매개변수 없음\n");
	printf("init B : 리턴 - node, 매개변수 없음\n");
	printf("init C : 리턴 - node 포인터, 매개변수 - 할당할 이름\n");
	
	printf("after_init A : %p\n\n", b);

	printf("before_init B : %p\n", &a);
	a = init_Node_B();
	printf("after_init B : %p\n\n", &a);


	printf("before_init C : %p\n", c);
	init_Node_C(&c);
	printf("after_init C : %p\n\n", c);

	while (1);
}