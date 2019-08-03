#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define tail NULL


typedef struct _node {
	int key;
	struct _node* next;
}node;

node *head;

int init_stack() {
	head = (node*)calloc(1, sizeof(node));
	head->next = tail;
}

int push(int data) {
	node *t;
	if ((t = (node*)malloc(sizeof(node))) == tail) {
		printf("Out of Memory\n");
		return -1;
	}
	
	t->key = data;
	t->next = head->next;
	head->next = t;
	
	return t;
}

int pop() {
	node *t;
	if ((t = head->next) == tail) {
		printf("Stack underflow\n");
		return -1;
	}
	int result;

	head->next = t->next;
	result = t->key;
	free(t);

	return t;
}

int print_stack(node *st) {
	node *t = st->next;
	int count = 1;
	while (t) {
		printf("out num %d : %d\n", count++, t->key);
		t = t->next;
	}
}

int clear(node *st) {
	node *s, *t;
	s = st->next;
	t = s->next;

	while (t) {
		free(s);
		s = t;
		t = t->next;
	}

	head->next = tail;
}


int main() {
	init_stack();
	push(1);
	push(2);
	push(3);
	push(4);
	push(5);
	push(6);
	push(7);
	push(8);
	push(9);

	print_stack(head);

	clear(head);

	print_stack(head);

	push(5);
	pop();
	pop();

	push(9);
	print_stack(head);
}