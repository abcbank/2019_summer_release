#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct _dnode {
	int key;
	struct _dnode *next;
	struct _dnode *pre;
}node;

node *head;
node *tail;

void init_quene() {
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->next = tail;
	tail->pre = head;
	head->pre = head;
	tail->next = tail;
}

void put(int data) {
	node *t;
	if ((t = (node*)calloc(1, sizeof(node)))== NULL) {
		printf("Out of memory\n\n");
		return -1;
	}
	t->key = data;
	t->next = tail;
	t->pre = tail->pre;
	tail->pre = t;
	t->pre->next = t;

	return 0;
}

int get() {
	node *t;
	int k;
	t = head->next;
	if (t == tail) {
		printf("Queue underflow\n\n");
		return -1;
	}
	k = t->key;
	head->next = t->next;
	t->next->pre = head;
	free(t);
	return k;
}

void main() {
	int i;
	init_quene();
	for (i = 0; i < 10; i++)
		put(i);
	for (i = 0; i < 10; i++)
		printf("get %d \n", get());

	while (1);
}