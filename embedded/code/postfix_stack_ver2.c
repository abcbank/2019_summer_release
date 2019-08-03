#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========스택 코드 시작=================
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType *s) {
	s->top = -1;
}
int is_empty(StackType *s) {
	return (s->top == -1);
}
int is_full(StackType *s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType *s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
element pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
element peek(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===========스택 코드 끝=================

int prec(char op) {  //연산자의 우선순위 반환
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}
void infix_to_postfix(char *exp, char *exp2) {
	int i = 0;
	char ch, top_op;
	char *dst = exp;
	int len = strlen(exp2);
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp2[i];
		switch (ch) {
		case '+': case '-': case '*': case '/':
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) 
				*dst++ = pop(&s);
			push(&s, ch);
			break;
		case '(':
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);
			while (top_op != '(') {
				*dst++ = top_op;
				top_op = pop(&s);
			}
			break;
		default:
			*dst++ = ch;
			break;
		}
	}
	while (!is_empty(&s))
		*dst++ = pop(&s);
	*dst = 0;
	/*while (!is_empty(&s))
		printf("%c", pop(&s));*/
	return;
}
int eval(char *exp)
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';   // 입력이 피연산자이면
			push(&s, value);
		}
		else {   //연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //연산을 수행하고 스택에 저장 
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}

int main() {
	char *s[100];
	char x[100];
	printf("중위 수식을 입력하시오>> ");
	scanf("%s", &s);
	printf("후위표식>> ");
	infix_to_postfix(x, s);
	printf("%s", x);
	printf("\n");
	eval(x);
	printf("결과 값은 %d입니다.\n", eval(x));
	return 0;
}