#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')

typedef struct _dnode {
	char key;
	struct _dnode *next;
	struct _dnode *pre;
}dnode;

dnode *head;
dnode *tail;

void init_lq(){
	head = (dnode*)malloc(sizeof(dnode));
	tail = (dnode*)malloc(sizeof(dnode));
	head->next = tail;
	tail->pre = head;
	tail->next = tail;
	head->pre = head;
}

void delete_lq() {
	dnode *t = head->next->next;
	while (t = tail) {
		free(t->pre);
		t = t->next;
	}

	head->next = tail;
	tail->pre = head;
}

void put_lq(int data) {
	dnode *t;
	if ((t = (dnode*)malloc(sizeof(dnode))) == NULL) {
		printf("stack overflow\n");
		return -1;
	}

	t->key = data;
	t->next = tail;
	tail->pre->next = t;
	t->pre = tail->pre;
	tail->pre = t;
}

int get_lq() {
	dnode *t=head->next;
	if (t == tail) {
		printf("stack underflow!\n\n");
		return -1;
	}
	int result = t->key;

	head->next = t->next;
	t->next->pre = head;

	free(t);

	return result;
	
}
void print_queue()
{
	dnode *t;
	t = head->next;
	while (t != tail) {
		printf("%-6d", t->key);
		t = t->next;
	}
	printf("\n");
}

int main(void) {
	int k;
	init_lq();

	put_lq(3);
	put_lq(6);
	put_lq(9);
	put_lq(1);
	put_lq(6);
	put_lq(3);
	print_queue();

	put_lq(4);
	put_lq(8);
	put_lq(7);
	put_lq(2);
	put_lq(0);

	init_lq();
	get_lq();
}