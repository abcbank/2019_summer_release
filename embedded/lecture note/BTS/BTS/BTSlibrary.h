#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "graphics.h"

#define	NODE	1
#define	LINK	2
#define	TAIL	4

#define DY		50

typedef int(*FCMP)(const void *, const void*);

typedef struct _node {
	struct _node *left;
	struct _node *right;
}node;

void init_tree(node **p);
void *btv_search(void *key, node *base, int *num, int width, FCMP fcmp);
void *btv_insert(void *key, node *base, int *num, int width, FCMP fcmp);
void _deleteall(node *t);
void *btv_deleteall(node *base, int *num);
void btv_sort_list(node *p, void(*fpr)(void *));
void btv_list(node *p, void(*fptr)(void *));
void _draw_node(node *p, void(*fptr)(void *, char *), int x1, int x2, int y, int mode);
void _draw_link(node *p, int x1, int x2, int y, int mode);
void btv_draw(node *p, void(*fptr)(void *, char *), int mode);
void _sort(node *p, void *a, int width);
node *_balance(int n, void *a, int width);
void btv_balance(node *base, int *num, int width);
