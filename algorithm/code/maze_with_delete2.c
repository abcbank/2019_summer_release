#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAZE_SIZE 19
#define MOUSE 2
//각 방향을 shift 연산을 통해 구현
#define UP 1
#define RIGHT 2
#define DOWN 4
#define LEFT 8

typedef struct rec {
	int x;
	int y;
	struct rec* nextnode;
}rec;

int maze[19][19] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                     {0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
                     {1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
	             {1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
	             {1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1},
	             {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
		     {1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1},
		     {1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
		     {1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
		     {1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
		     {1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1},
		     {1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
		     {1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1},
		     {1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
		     {1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
		     {1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    		     {1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
		     {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
		     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
void gotoxy(int x, int y) {	//좌표 이동 함수
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

rec* init_node() {	//구조체 초기화 함수
	rec* node=(rec*)calloc(1,sizeof(rec));
	return node;
}

int still_in_maze(int x, int y) {	//미로 내에 있는지 확인하는 함수
	if (x > 0 && x <= MAZE_SIZE - 1 && y > 0 && y <= MAZE_SIZE - 1)
		return 1;
	else
		return 0;
}

int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir) {// 벽이 앞에 있는지 확인하는 함수
	x = (dir == LEFT) ? --(x) : (dir == RIGHT) ? ++(x) : x;
	y = (dir == UP) ? --(y) : (dir == DOWN) ? ++(y) : y;
	return m[y][x];
}

void record(rec* node, int x, int y) { //구조체 리스트를 통해 이동 기록을 저장하는 함수
	rec *tmp = init_node();
	tmp->x = x;
	tmp->y = y;
	node->nextnode = tmp;
}

void forward(int *x, int *y, int dir,rec*node) {	// 앞으로 전진하는 함수
	gotoxy(*x + 1, *y + 1);
	_putch(' ');
	*x = (dir == LEFT) ? --(*x) : (dir == RIGHT) ? ++(*x) : *x;
	*y = (dir == UP) ? --(*y) : (dir == DOWN) ? ++(*y) : *y;
	record(node,*x, *y);
	gotoxy(*x + 1, *y + 1);
	_putch(MOUSE);
}

void turn_right(int *dir) {	// 오른쪽으로 회전하는 함수
	*dir <<= 1;
	*dir = (*dir > LEFT) ? UP : *dir;
}

void turn_left(int *dir) {	// 왼쪽으로 회전하는 함수
	*dir >>= 1;
	*dir = (*dir < UP) ? LEFT : *dir;
}

void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir, rec* root) {	//오른손 법칙 알고리즘
	rec *pre = init_node();
	pre->x = x;
	pre->y = y;
	root->nextnode = pre;
	gotoxy(x + 1, y + 1);
	_putch(MOUSE);

	forward(&x, &y, dir, pre);
	pre = pre->nextnode;
	while (still_in_maze(x, y)) {
		for (int i = 0; i < 50000000; i++) {}
		turn_right(&dir);
		while (wall_ahead(m, x, y, dir))
			turn_left(&dir);
		forward(&x, &y, dir,pre);
		pre = pre->nextnode;
	}
}

rec* delete_way(rec*tmp, rec*node) {	//경로 지우는 함수
	tmp->nextnode = node->nextnode;
	return node->nextnode;
}

void right_hand_delete(rec*node) {	// 짧은 경로 찾는 함수

	rec*tmp = node->nextnode;

	while (tmp->nextnode != NULL) {

		rec* pre = tmp->nextnode;

		while (pre->nextnode != NULL) 
			pre = ((pre->x == tmp->x) && (pre->y == tmp->y)) ? delete_way(tmp, pre) : (pre->nextnode);

		tmp = tmp->nextnode;

	}
}

void print_maze() {	//출력하는 함수
	int x, y;
	for (y = 0; y < MAZE_SIZE; y++) {
		if (y == 0) gotoxy(0, 1);
		for (x = 0; x < MAZE_SIZE; x++) {
			if (x == 0) printf(" ");
			if (maze[y][x] == 1) printf("%%");
			else printf(" ");
		}
		printf("\n");
	}
}
void main() {	
	int dir = LEFT;
	int sx = MAZE_SIZE - 2, sy = MAZE_SIZE - 2;
	rec *root=init_node();
	rec *node = root;

	print_maze();
	right_hand_on_wall(maze, sx, sy, dir, root);
	//right hand on wall

	right_hand_delete(root);
	//get shortest route

	node = node->nextnode;
	while (node->nextnode != NULL) {
		for (int i = 0; i < 50000000; i++) {}
		gotoxy(node->x + 1, node->y + 1);
		_putch(MOUSE);
		node = node->nextnode;
	}
	free(root);
}
