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

void print_list(node *t)
{
	while (t != NULL) {
		printf("%-8d", t->data);
		t = t->next;
	}
}

int main(void) {
	node root;
	node *tmp, *pr = &root;

	root.data = 0;
	root.next = NULL;

	tmp = init_Node_C(9);
	pr->next = tmp;
	pr = pr->next;

	tmp = init_Node_C(3);
	pr->next = tmp;
	pr = pr->next;

	tmp = init_Node_C(5);
	pr->next = tmp;
	pr = pr->next;

	tmp = init_Node_C(1);
	pr->next = tmp;
	pr = pr->next;

	tmp = init_Node_C(7);
	pr->next = tmp;
	pr = pr->next;

	tmp = init_Node_C(6);
	pr = &root;
	while (1) {
		if (pr->data == 5) {
			tmp->next = pr->next;
			pr->next = tmp;
			break;
		}
		pr = pr->next;
	}
	print_list(&root);

	printf("\n\n");

	pr = &root;
	while (1) {
		if (pr->next->data == 5) {
			node *t = pr->next;
			pr->next = t->next;
			free(t);
			break;
		}
		pr = pr->next;
	}
	print_list(&root);
	while(pr){
	pr = &root;
	while (pr->next) 
		pr = pr->next;
	free(pr);
	}
	while (1);
}