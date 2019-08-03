#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define tail NULL


typedef struct _node {
	char key;
	struct _node* next;
}node;

node *head;

int init_stack() {
	head = (node*)calloc(1, sizeof(node));
	head->next = NULL;
}

int push(char data) {
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

char pop() {
	node *t;
	char result;
	if ((t = head->next) == tail) {
		printf("Stack underflow\n");
		return -1;
	}


	head->next = t->next;
	result = t->key;
	free(t);

	return result;
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

void postfix(char *dst, char *src)
// dst : destination -> postfix, src : source -> infix
{
	char c;
	init_stack();
	while (*src) {
	// while source exist
		if (*src == ')')
		{
			*dst++ = pop();
			// pop saved operation in dst and dst++
			*dst++ = ' ';
			src++; 
		}
		else if (*src == '+' || *src == '-' ||
			*src == '*' || *src == '/')
		{
			push(*src);
			// save operation in stack
			src++;
		}
		else if (*src >= '0' && *src <= '9')
		// if *src(value of src) is num
		{
			do {
				*dst++ = *src++;
				// save value in dst and src++
			} while (*src >= '0' && *src <= '9');
			// until *src is not num
			*dst++ = ' ';
		}
		else
			src++;
			// if value of src is useless, get next pointer
	} // end while
	*dst = 0;
	// dst -> string. end of string = NUL
}

void main() {
	char exp[256];
	char src[256] = "(1 + (2 * 3))";
	postfix(exp, src);
	printf("Postfix representation : %s\n", exp);
}
