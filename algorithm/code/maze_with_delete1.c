#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAZE_SIZE 19
#define MOUSE 2
#define UP 1
#define RIGHT 2
#define DOWN 4
#define LEFT 8
//typedef enum direction { UP , RIGHT , DOWN , LEFT } direction;

int *rec;
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
					 {1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1},
					 {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
					 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
void gotoxy(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int still_in_maze(int x, int y) {
	if (x > 0 && x <= MAZE_SIZE - 1 && y > 0 && y <= MAZE_SIZE - 1)
		return 1;
	else
		return 0;
}

int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir) {
	x = (dir == LEFT) ? --(x) : (dir == RIGHT) ? ++(x) : x;
	//	 [(dir == LEFT) ? --(*x) : {(dir == Right) ? ++(*x) : *x}];
	y = (dir == UP) ? --(y) : (dir == DOWN) ? ++(y) : y;
	return m[y][x];
}

void record(int x, int y) {
	static int index = 0;
	rec[index++] = x;
	rec[index++] = y;
}

void forward(int *x, int *y, int dir) {
	gotoxy(*x + 1, *y + 1);
	_putch(' ');
	*x = (dir == LEFT) ? --(*x) : (dir == RIGHT) ? ++(*x) : *x;
	//	 [(dir == LEFT) ? --(*x) : {(dir == Right) ? ++(*x) : *x}];
	*y = (dir == UP) ? --(*y) : (dir == DOWN) ? ++(*y) : *y;
	//record(*x, *y);
	gotoxy(*x + 1, *y + 1);
	_putch(MOUSE);
}

void turn_right(int *dir) {
	*dir <<= 1;
	*dir = (*dir > LEFT) ? UP : *dir;
}

void turn_left(int *dir) {
	*dir >>= 1;
	*dir = (*dir < UP) ? LEFT : *dir;
}

void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir) {
	gotoxy(x + 1, y + 1);
	_putch(MOUSE);

	forward(&x, &y, dir);

	while (still_in_maze(x, y)) {
		for (int i = 0; i < 50000000; i++) {}
		turn_right(&dir);
		while (wall_ahead(m, x, y, dir))
			turn_left(&dir);
		forward(&x, &y, dir);
	}
}
void print_maze() {
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

void deletePath(int i, int j)
//j=2*n+i, n은 
{
//    int k = i;  
    //i값 보존
    while (rec[j] >= 0)
    //j 기준으로 스택이 끝날때까지
        rec[i++] = rec[j++];
    //한칸씩 앞으로 당긴다. 한마디로 stack 한 쌍 삭제
    rec[i] = -1;
    //0 이하로 초기화 안해주면 getShortestPath 내의 while문에서 오류 생김
//   return k;
}

void getShortestPath()
{
    int i = 0;
    //i=0, rec는 스택 형태이므로 가장 처음 집어넣은 값을 의미. 기준 노드
    while (rec[i] >= 0) 
    //calloc을 통해 모든 항을 0으로 초기화. 만약 -1이 나오면 스택이 끝난것.
    {
        int j = i + 2;  
        //2 -> x(혹은 y) 좌표만 참조하기 위한 설정.        
        while (rec[j] >= 0)
        //=스택이 끝날때까지
        {
            if (rec[i] == rec[j]&&rec[i+1]==rec[j+1])
            //=만약 두 node의 위치가 같고           
            {
                for (int k = i; k <= j - 2; k++) 
                    deletePath(i, j);
                //i,j 사이의 값을 삭제, 매개변수 j=2*n+i
                j = i + 2;
                //기준 노드의 위치가 바꼈으므로 기준노드 다음 노드로 초기화
            }
            else
            {
                j += 2;
            }
        }
        i+=2;
    }
}

void main() {
    rec=(int*)calloc(MAZE_SIZE*MAZE_SIZE,sizeof(int));
	int dir = LEFT;
	int sx = MAZE_SIZE - 1, sy = MAZE_SIZE - 1;
	print_maze();

	right_hand_on_wall(maze, sx, sy, dir);
    getShortestPath();
	while (1);
}
