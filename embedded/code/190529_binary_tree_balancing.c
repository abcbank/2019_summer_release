#include<stdio.h>
#include<stdlib.h>
#define MAX_NODE 100
typedef struct _node {
	int key;
	struct _node *left;
	struct _node *right;
}node;

node *head;
int *size;
int *index;
int inorder[MAX_NODE];

node *btInorder(node *base, int *inorder, int *index);
node *btInsert(node *base, int *size, int key);
node *btDelete(node *base, int *size, int key);
node *btSearch();
node *btBalance();

int main(void){}

node *btInorder(node *base, int *inorder, int *index) {
	if (base) {
		bti_sort(base->left, inorder, index);
		inorder[(*index)++] = base->key;
		bti_sort(base->right, inorder, index);
	}
}

node *btInsert(node *base, int *size, int key) {
	// 탐색에 사용할 두 node 선언
	node *current = base;
	node *next = base->left;

	while (next != NULL) {
		current = next;

		// current node의 상태에 따라 다음 node를 결정. 
		if (key < current->key) next = current->left;
		else current = current->right;
	}

	// 이때, next는 NULL이었던 것을 기억하자.
	next = (node*)malloc(sizeof(node));

	// 상태 초기화
	next->key = key;
	next->left = NULL;
	next->right = NULL;

	// 현재 위치의 key 값에 따라 next를 넣을 위치 조정
	if (key < current->key || current == base) current->left = next;
	else current->right = next;

	// 총 node수가 늘어났으므로 size는 증가
	(*size)++;
	return s;
}

node *btDelete(node *base, int *size, int key){
	node *parent, *son, *del, *nexth;
	parent = base;
	del = base->left;
	while (key != del->key && del != NULL) {
		parent = del;
		if (del->key > key) del = del->left;
		else del = del->right;
	}

	if (del->right == NULL) son = del->left;

	else if (del->right->left == NULL) {
		son = del->right;
		son->left = del->left;
	}

	else {
		nexth = del->right;
		while (nexth->left->left != NULL) nexth = nexth->left;
		son = nexth->left;
		nexth->left = son->right;
		son->left = del->left;
		son->right = del->right;
	}

	if (key < parent->key || parent == base)
		parent->left = son;
	else
		parent->right = son;
	free(del);
	(*size)--;
	return parent;

}

node *btSearch();

node *btBalance();