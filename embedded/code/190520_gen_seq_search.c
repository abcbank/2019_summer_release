#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef int(*FCMP)(const void *, const void *);

#define size_t int
#define SIZE 10
#define int2name(i) (i + 'A')

//--------------------------------------------------------------------------

#define BASE(i) ((char *)base + (i)*width)

int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);

//--------------------------------------------------------------------------

//===========================================================================

#define tail NULL


typedef struct _node {
	//	void *key;
	struct _node *next;
}node;

node *head;

void initList(node **p);
int llvSearch(void *key, node*base, size_t *num, size_t width, FCMP fcmp);
node *llvInsert(void *key, node*base, size_t *num, size_t width, FCMP fcmp);
node* llvDelete(void *key, node*base, size_t *num, size_t width, FCMP fcmp);
void llfvSearch(void *key, node*base, size_t *num, size_t width, FCMP fcmp);


//===========================================================================

void initArr(int *arr, int size) {
	for (int i = 0; i < size; i++)
		*arr++ = rand() % 26;
}

int intcmp(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
	// return (*(int * )a > *(int *)b);
}

int LLcmp(node *a, const void *b) {
	return *(int*)(a + 1) - *(int*)b;
}

int main(void) {
	node *t;
	int base[SIZE];
	int size = sizeof(base) / sizeof(int);
	int index;
	int i;
	FCMP fcmp = intcmp;

	srand((unsigned int)time(NULL));
	initArr(base, SIZE);

	//for (i = 0; i < 32; i++) {
	//	if ((index = lv_search(&i, base, &size, sizeof(base[0]), fcmp)) > 0)
	//		printf("%c : %d\n", int2name(i), index);
	//}

	initList(&head);
	initArr(base, SIZE);
	
	for (i = 0; i < SIZE; i++) {
		llvInsert(base+i, head, &size, sizeof(base[0]), fcmp);
	}

	for (node *t = head->next; t; t = t->next) {
		printf("%c  ",int2name(*(int*)(t + 1)));
	}
	printf("\n\n");
	for (i = 0; i < 26; i++) {
		if ((index = llvSearch(&i, head, &size, sizeof(base[i]), fcmp)) > 0)
			printf("%c : %d index\n", int2name(i), index);
	}
	while (1);
}

int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int i = 0;
	while (fcmp(BASE(i), key) != 0 && i < *num) i++;
	return (i < *num ? i : -1);
}

int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	memcpy(BASE((*num++)), key, width);
	return *num - 1;
}

int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int p, i;
	if (*num > 0) {
		if ((p = lv_search(key, base, num, width, fcmp)) < 0)
			return -1;
		for (i = p + 1; i < *num; i++) {
			memcpy(BASE(i), BASE(i + 1), width);
			(*num)--;
			return p;
		}
		return -1;
	}
}

int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
	int i = 0, j;
	void *v;
	while (fcmp(BASE(i), key) != 0 && i < *num) i++;
	if (i >= *num) return - 1;
	v = malloc(width);
	memcpy(v, BASE(i), width);
	for (j = i - 1; j >= 0; j--)
		memcpy(BASE(j+1), BASE(j), width);
	memcpy(BASE(0), v, width);
	return 0;
}
//=============================================================================
void initList(node **p) {
	*p = (node*)malloc(sizeof(node));
	(*p)->next = NULL;
}

int llvSearch(void *key, node*base, size_t *num, size_t width, FCMP fcmp) {
	node *t;
	int cnt= 1;
	t = base->next;
	while (t != NULL && fcmp(t + 1, key) != 0) { 
		t = t->next; 
		cnt++;
	}
	return (t == NULL ? -1 : cnt);
}

node *llvInsert(void *key, node*base, size_t *num, size_t width, FCMP fcmp)
{
	node *t = (node*)malloc(sizeof(node)+width);
	t->next = tail;
	memcpy(t + 1, key, width);

	t->next = base->next;
	base->next = t;

	return t;
}

node* llvDelete(void *key, node*base, size_t *num, size_t width, FCMP fcmp) {
	node *t;
	if (base->next){
		if ((t = llvSearch(key, base, num, width, fcmp)) < 0)
			return -1;
		for (t = t; t->next; t= t->next) {
			memcpy(t+1, (t->next) +1, width);
			return t;
		}
		return -1;
	}

}

void llfvSearch(void *key, node*base, size_t *num, size_t width, FCMP fcmp) {
	int i = 0, j;
	void *v;
	while (fcmp(base + 1, key) != 0 && base) base = base->next;
	if (!base) return - 1;
	v = malloc(width);
	memcpy(v, base + 1, width);
	for (j = i - 1; j >= 0; j--)
		memcpy(BASE(j+1), BASE(j), width);
	memcpy(BASE(0), v, width);
	return 0;

}
