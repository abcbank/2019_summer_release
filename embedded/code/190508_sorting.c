#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 10000
#define MAX_SIZE 10000
#define notprint 0
#define UNSEEN -INT_MAX
#define MAX_NODE 10000
#define name2int(c) (c-'A')
#define int2name(c) (c+'A')

int mode = 0;
int check[MAX_NODE];   // 가중치 저장
int h[MAX_NODE];   // 힙
int parent[MAX_NODE];   // 부모 노드 저장
int nheap = 0;
// -----------------------------------------heap function

void pq_init();
// heap 초기화 함수
int pq_empty();
// heap 내의 데이터를 비우는 함수
void upheap(int *a, int k);
// up heap : 주어진 index를 기준으로 위로 올라가며 정렬
// a : heap, k : index num
void downheap(int *a, int k);
// down heap : 주아전 index를 기준으로 아래로 내려가며 정렬
// a : heap, k : index num
void insert(int *a, int *N, int v);
// heap에 데이터를 추가함
// a : heap, N : index size, v : weight
void adjust_heap(int h[], int n);
// 모든 index에 대해 down heap을 실행
// h : heap, n : index size
int extract(int *a);
// root의 값을 뺴오는 함수
// a : heap

// -----------------------------------------end

void heap_sorting_A(int *a, int N);
void heap_sorting_B(int *a, int N);
void init_arr(int *arr, int size);
void printArr(int arr[], int size) {
	int i = 0;
	while (i < size) {
		printf("%2d", *(arr + i++));
	}
}
int stack[MAX_SIZE];
int top;

int index[SIZE];

void select_sort(int *a, int N);
void gen_select_sort(void *base, size_t nelem, size_t width, int(*fcmp)(const void *, const void *));
void insert_sort(int *a, int N);
void gen_insert_sort(void *a, size_t nelem, size_t width, int(*fcmp)(const void *, const void *));
void shell_sort(int *a, int N);
void gen_shell_sort(int *a, size_t nelem, size_t width, int(*fcmp)(const void *, const void *));
void re_quick_sort(int *base, int N);
void gen_re_quick_sort(void *base, size_t N, size_t width, int(*fcmp)(const void *, const void *));
void nr_quick_sort(int *base, int N);
void gen_nr_quick_sort(void *base, size_t N, size_t width, int(*fcmp)(const void *, const void *));
// stack function
void push(int data) {
	stack[++top] = data;
}

int pop() {
	return stack[top--];
}

int stack_empty() {
	return top == -1;
}

void init_stack() {
	top = -1;
}
// end stack function

int intcmp(const void *a, const void *b);
void print(int *arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%2d", *(arr + i));
	}
	printf("\n");
}
void op_insert_sort(void *a, size_t nelem, size_t width, int(*fcmp)(const void *, const void *)) {
	int i, j;
	void *t = malloc(width);
	for (i = 0; (unsigned int)i < nelem; i++)
		index[i] = i;
	for (i = 1; (unsigned int)i < nelem; i++)
	{
		memcpy(t, (char*)index + i * width, width);
		j = i;
		while (j > 0 && fcmp((char*)a + *((index)+(j - 1))*width, (char*)a + (*(int*)t) * width))
		{
			memcpy((char*)index + j * width, (char*)index + (j - 1) * width, width);
			j--;
		}
		memcpy((char*)index + j * width, (char*)t, width);
	}
}

void arrcpy(int *src, int *dst) {
	int i;
	for (i = 0; i < SIZE; i++) {
		*(dst++) = *(src++);
	}
}

void init_arr(int *src, int size) {
	for (int i = 0; i < SIZE; i++) {
		src[i] = rand() % 10;
	}
}

int main() {
	LARGE_INTEGER freq, start, stop;
	double diff;
	char x = NULL;
	int arr[SIZE];
	int arr2[SIZE];
	srand((unsigned)time(NULL));
	int(*cmp)(const void *, const void *) = intcmp;

	printf("Print result?\n");
	printf("1. Yes   2. No\n");
	printf("Input>> ");
	scanf("%d", &mode);
	getchar();
	mode = (mode == 1) ? !notprint : notprint;

	init_arr(arr, SIZE);
	if (!mode == notprint) {
		printf("given array : ");
		print(arr, sizeof(arr) / sizeof(int));
	}
	// Select Sort
	printf("\n---------------\n");
	printf("Select Sorting\n");
	printf("---------------\n");

	arrcpy(arr, arr2);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	select_sort(arr2, SIZE);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("1. Select Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
	}

	arrcpy(arr, arr2);


	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	gen_select_sort(arr2, SIZE, sizeof(int), cmp);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("2. Generalized Select Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
	}

	// Insert Sort -> index 내의 번호를 바꿈
	printf("\n--------------\n");
	printf("Insert Sorting\n");
	printf("--------------\n");
	arrcpy(arr, arr2);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	insert_sort(arr2, SIZE);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("1. Insert Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
		printf("Index : ");
		print(index, sizeof(index) / sizeof(int));
		printf("Result : ");
		for (int k = 0; k < SIZE; k++)
			printf("%2d", arr2[index[k]]);
		printf("\n");
	}

	arrcpy(arr, arr2);

	//Generalized Insert Sort -> index 내의 번호를 바꿈
	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	op_insert_sort(arr2, SIZE, sizeof(int), cmp);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("2. Generalized Insert Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
		printf("Index : ");
		print(index, sizeof(index) / sizeof(int));
		printf("Result : ");
		for (int k = 0; k < SIZE; k++)
			printf("%2d", arr2[index[k]]);
		printf("\n");
	}

	// shell sort
	printf("\n-------------\n");
	printf("Shell Sorting\n");
	printf("-------------\n");

	arrcpy(arr, arr2);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	shell_sort(arr2, SIZE);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("1. Shell Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
	}

	arrcpy(arr, arr2);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	gen_shell_sort(arr2, SIZE, sizeof(int), cmp);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("2. Generalized Shell Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
	}


	// Quick Sort
	printf("\n-------------\n");
	printf("Quick Sorting\n");
	printf("-------------\n");

	arrcpy(arr, arr2);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	re_quick_sort(arr2, SIZE);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("1. Recursive Quick Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
	}

	// Generalized Recursive Quick Sort
	arrcpy(arr, arr2);

	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	gen_re_quick_sort(arr2, SIZE, sizeof(int), cmp);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("2. Generalized Recursive Quick Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
	}

	arrcpy(arr, arr2);

	// Non-recursive Quick Sort
	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	nr_quick_sort(arr2, SIZE);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("3. Non-recursive Quick Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
	}

	// Generalized Non-recursive Quick Sort
	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	gen_nr_quick_sort(arr2, SIZE, sizeof(int), cmp);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

	printf("4. Generalized Non-recursive Quick Sort : %f\n", diff);

	if (!mode == notprint) {
		printf("Array : ");
		print(arr2, sizeof(arr2) / sizeof(int));
	}

	srand((unsigned int)time(NULL));
	printf("\n------------\n");
	printf("Heap Sorting\n");
	printf("------------\n");
	printf("1. Heap Sorting A : w/ upheap, downheap\n");
	arrcpy(arr, arr2);
	if (mode == 1) {
		printf("src    :");
		printArr(arr2, sizeof(arr2) / sizeof(int));
		printf("\nresult :");
	}
	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	heap_sorting_A(arr2, sizeof(arr2) / sizeof(int));

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("require time : %f", diff);



	// 원래는 배열의 원소들을 그대로 heap에 대입해줘야하지만 귀찮으니 그냥 자체를 하나의 heap으로 간주
	// 단, heap의 첫번째 항은 사용하지 않는다는걸 주의하자.
	printf("\n2. Heap Sorting B : w/ downheap");
	arrcpy(arr, arr2); 
	if (mode == 1) {
		printf("\nsrc    :");
		printArr(arr2, SIZE);
		printf("\nresult :");
	}
	QueryPerformanceFrequency(&freq); // computer frequency
	QueryPerformanceCounter(&start); // starting point

	heap_sorting_B(arr2, sizeof(arr2) / sizeof(int) - 1);

	QueryPerformanceCounter(&stop); // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("\nrequire time : %f", diff);
	// heap sorting의 경우, 알고리즘 내에 printf 등 출력 함수가 포함되기 때문에 상대적으로 오래걸린다.
	while (!x) { x = getchar(); };
}
void shell_sort(int *a, int N)
{
	int i, j, k, h, v;
	for (h = N / 2; h > 0; h = h >> 1) {
		for (i = 0; i < h; i++) {
			for (j = i + h; j < N; j += h) {
				v = a[j];
				k = j;
				while (k > h - 1 && a[k - h] > v) {
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
}

void gen_shell_sort(int *a, size_t nelem, size_t width, int(*fcmp)(const void *, const void *))
{
	int i, j, k, h;
	void *v = malloc(width);
	for (h = nelem / 2; h > 0; h /= 2) {
		for (i = 0; i < h; i++) {
			for (j = i + h; (unsigned int)j < nelem; j += h) {
				memcpy(v, (char*)a + j * width, width);
				k = j;
				while (k > h - 1 && fcmp((char*)a + (k - h)*width, (char*)v)) {
					a[k] = a[k - h];
					k -= h;
				}
				memcpy((char*)a + k * width, v, width);
			}
		}
	}
}

void insert_sort(int *a, int N) {
	int i, j, t;
	for (i = 0; i < N; i++)
		index[i] = i;
	for (i = 1; i < N; i++)
	{
		t = index[i];
		j = i;
		while (j > 0 && a[index[j - 1]] > a[t])
		{
			index[j] = index[j - 1];
			j--;
		}
		index[j] = t;
	}
}

void gen_insert_sort(void *a, size_t nelem, size_t width, int(*fcmp)(const void *, const void *)) {
	void *t;
	int i, j;
	t = malloc(width);
	for (i = 1; (unsigned int)i < nelem; i++) {
		memcpy(t, (char*)a + i * width, width);
		j = i;
		// 초기값을 min_value라 가정, index와 value를 저장한다.
		while (j > 0 && fcmp((char*)a + (j - 1)*width, t)) {
			memcpy((char*)a + j * width, (char*)a + (j - 1)*width, width);
			j--;
		}
		memcpy((char*)a + j * width, (char*)t, width);
	}
	free(t);
}

int intcmp(const void *a, const void *b)
{
	return (*(int *)a > *(int *)b);
}

void select_sort(int *a, int N) {
	int min, tmp;
	// 가장 작은 값
	int min_idx;
	// 가장 작은 값의 인덱스 번호
	int x, y;
	// 2중 loop를 구현하기 위해 사용하는 변수 두가지

	for (y = 0; y < N - 1; y++) {
		// N-1번째 항의 경우, 뒤에 항이 없으므로 이후 항들 중 최하값이 자기 자신이 될수밖에 없다.
		min_idx = y;
		// 다음 항 중 아무 값도 참조하지 않은 상태이므로 min_index가 y가 된다.
		min = a[y];
		// 같은 맥락으로 가장 작은 값은 a[y]가 됨
		tmp = a[y];
		// min값은 이후 탐색 루프를 돌다 없어질 가능성이 높으므로 후에 위치를 바꿀때를 대비해 하나 저장해둠.
		for (x = y + 1; x < N; x++) {
			// 이후 존재하는 나머지 항들에 대해 가장 작은 값을 가져간다.
			if (min > a[x]) {
				min = a[x];
				min_idx = x;
			}
		}
		a[min_idx] = a[y];
		a[y] = min;
		// 선택된 값(a[y])와 이후 항들 중 가장 작은 값(a[min_idx])의 위치를 바꿔준다.
	}
}

void gen_select_sort(void *base, size_t nelem, size_t width,
	int(*fcmp)(const void *, const void *))
	// base <-> a, nelem <-> N
	// width : 자료형의 크기
	// fcmp : 지정된 메모리 위치 내의 크기를 특정 상수와 비교하는 함수
{
	void *min;
	// min : 최소값. 다만 메모리 축소를 위해 포인터로 선언
	int min_idx;
	int x, y;
	min = malloc(width);
	// min에 자료형만큼 할당해줌
	for (y = 0; (unsigned int)y < nelem - 1; y++)
	{
		min_idx = y;
		memcpy(min, (char *)base + y * width, width);
		// a[y] = (char*)base + y*width,width 
//		printf("%d\t", *(int *)min);
		for (x = y + 1; (unsigned int)x < nelem; x++)
		{
			if (fcmp(min, (char *)base + x * width) > 0)
				// min과 a[x]의 값을 비교한다.
			{
				memcpy(min, (char *)base + x * width, width);
				// 만약 결과가 0보다 크면 min값을 변경
				min_idx = x;
				// 최소값의 인덱스값도 변경 
			}
		}
		memcpy((char *)base + min_idx * width, (char*)base + y * width, width);
		memcpy((char *)base + y * width, min, width);
		//		print((int*)base);
		//		printf("\n\n");
	}
}

void gen_re_quick_sort(void *base, size_t N, size_t width, int(*fcmp)(const void *, const void *)) {
	void *pivot = malloc(width);
	void *temp = malloc(width);
	// value는 배열 내 원소의 크기를 따라가므로 void형 포인터로 선언
	int i = -1, j = N - 1;
	// index는 정수이므로 int형으로 선언
	if (N > 1) {
		memcpy(pivot, (char*)base + (N - 1)*width, width);
		while (1) {
			while (fcmp(pivot, (char*)base + ++i*width));
			// pivot보다 큰 바닥에서 제일 가까운 항을 찾는다.
			while (fcmp((char*)base + --j*width, pivot));
			// pivot보다 작은 천장에서 가장 가까운 항을 찾는다.
			if (i >= j) break;
			// 정지 조건 : 아래에서 올라오는 index와 위에서 내려오는 index가 서로 마주쳤을 경우
			memcpy(temp, (char*)base + i * width, width);
			memcpy((char*)base + i * width, (char*)base + j * width, width);
			memcpy((char*)base + j * width, temp, width);
			// 정지 조건이 아닐 경우, 두 항의 위치를 바꿔준다.
		}
		memcpy(temp, (char*)base + i * width, width);
		memcpy((char*)base + i * width, (char*)base + (N - 1)*width, width);
		memcpy((char*)base + (N - 1)*width, temp, width);
		// pivot을 항 중간에 끼워넣는다
		// i 이하 = pivot보다 작은 항들의 배열, j 이상 -> pivot보다 큰 항들의 배열
		// 따라서 i 다음 항에 pivot을 끼워넣음

		//base[N : i : 0] -> base[N : i] -> pivot보다 작거나 같은 항들의 모임
		//123496785 				 	 -> pivot보다 크거나 같은 항들의 모임
		gen_re_quick_sort(base, i, width, fcmp);
		// base -> 1234 정렬
		gen_re_quick_sort((char*)base + (i + 1)*width, N - i - 1, width, fcmp);
		// base -> 97858 정렬
	}
}

void nr_quick_sort(int *base, int N) {
	int pivot, temp;
	int bottom = 0, ceiling = N - 1;
	// 각각 while문 내에서 바닥과 천장을 알려주는 역할
	int up2down, down2up;
	// 위에서 아래로 내려가는 index, 아래에서 위로 올라가는 index
	init_stack();

	push(bottom);
	push(ceiling);

	while (!stack_empty()) {
		ceiling = pop();
		bottom = pop();
		// 바닥과 천장을 pop
		if (ceiling - bottom > 0) {
			// 바닥과 천장이 같으면 해당 배열의 크기는 1이다. 따라서 정렬을 해줄 필요가 없다. 
			pivot = base[ceiling];
			// 마지막 항을 pivot이라 설정
			down2up = bottom - 1;
			up2down = ceiling;
			// 양 끝에 index 설정. pre-increase system이므로 1씩 빼준다.
			while (1) {
				while (base[++down2up] < pivot);
				while (base[--up2down] > pivot);
				if (down2up > up2down) break;
				temp = base[down2up];
				base[down2up] = base[up2down];
				base[up2down] = temp;
			}
			temp = base[ceiling];
			base[ceiling] = base[down2up];
			base[down2up] = temp;
			// re와 알고리즘 동일

			push(down2up);
			push(ceiling);
			// pivot보다 숫자가 큰 부분의 시작과 끝 index를 push해준다.
			push(bottom);
			push(down2up - 1);
			// pivot보다 숫자가 작은 부분의 시작과 끝 index를 push해준다.
		}
	}
}

void gen_nr_quick_sort(void *base, size_t N, size_t width, int(*fcmp)(const void *, const void *)) {
	void *pivot = malloc(width);
	void *temp = malloc(width);
	int bottom = 0, ceiling = N - 1;
	int up2down, down2up;
	init_stack();
	push(bottom);
	push(ceiling);
	while (!stack_empty()) {
		ceiling = pop();
		bottom = pop();
		if (ceiling - bottom > 0) {
			memcpy(pivot, (char*)base + ceiling * width, width);
			down2up = bottom - 1;
			up2down = ceiling;
			while (1) {
				while (fcmp(pivot, (char*)base + (++down2up)*width));
				while (fcmp((char*)base + (--up2down)*width, pivot));
				if (down2up > up2down) break;
				memcpy(temp, (char*)base + down2up * width, width);
				memcpy((char*)base + down2up * width, (char*)base + up2down * width, width);
				memcpy((char*)base + up2down * width, temp, width);
			}

			memcpy(temp, (char*)base + ceiling * width, width);
			memcpy((char*)base + ceiling * width, (char*)base + down2up * width, width);
			memcpy((char*)base + down2up * width, temp, width);
			push(down2up);
			push(ceiling);
			push(bottom);
			push(down2up - 1);
		}
	}
}
void re_quick_sort(int *base, int N) {
	//base[N : 0]
	//123456789
	int pivot, temp;
	int i = -1, j = N - 1;
	if (N > 1) {
		// N이 1보다 작을 경우, 해당 배열의 size가 1 이하라는 의미이다.
		pivot = base[N - 1];
		// pivot을 배열의 마지막 항으로 설정
		while (1) {
			while (base[++i] < pivot);
			// pivot보다 큰 바닥에서 제일 가까운 항을 찾는다.
			while (base[--j] > pivot);
			// pivot보다 작은 천장에서 가장 가까운 항을 찾는다.
			if (i >= j) break;
			// 정지 조건 : 아래에서 올라오는 index와 위에서 내려오는 index가 서로 마주쳤을 경우
			temp = base[i];
			base[i] = base[j];
			base[j] = temp;
			// 정지 조건이 아닐 경우, 두 항의 위치를 바꿔준다.
		}

		temp = base[i];
		base[i] = base[N - 1];
		base[N - 1] = temp;
		// pivot을 항 중간에 끼워넣는다
		// i 이하 = pivot보다 작은 항들의 배열, j 이상 -> pivot보다 큰 항들의 배열
		// 따라서 i 다음 항에 pivot을 끼워넣음

		//base[N : i : 0] -> base[N : i] -> pivot보다 작거나 같은 항들의 모임
		//123496785 				 	 -> pivot보다 크거나 같은 항들의 모임
		re_quick_sort(base, i);
		// base -> 1234 정렬
		re_quick_sort(base + i + 1, N - i - 1);
		// base -> 97858 정렬
	}
}

void heap_sorting_A(int *a, int N)
{
	int i;
	pq_init();
	for (i = 0; i < N; i++)
		insert(h, &nheap, a[i]);
	for (i = nheap; i > 0; i--) {
		if (mode == 1)
			printf("%2d", extract(h));
		else
			extract(h);
	}
	if(mode==1)
		printf("\n");
}

void pq_init() {
	nheap = 0;
	// set node size of heap zero
}

int pq_empty() {
	if (nheap == 0) return 1;
	return 0;
	// if empty : true
	// else : false
}

void adjust_heap(int h[], int n) {
	int k;
	for (k = n / 2; k >= 1; k--)
		downheap(h, k);
	// downheap all nodes except leaf nodes
}

void upheap(int *a, int k) {
	int v;
	v = a[k];
	while (a[k / 2] < v && k / 2>0) {
		// if weight of children of k is smaller than weight of v,
		// ps. weight of unvisited nodes are minus
		a[k] = a[k / 2];
		k = k >> 1;
	}
	a[k] = v;
}

void downheap(int *a, int k) {
	// N : node number of tree
	int i, v;
	v = a[k];
	while (k <= nheap / 2) {
		i = k << 1;
		if (i < nheap&& a[i] < a[i + 1]) i++;
		if (v >= a[i]) break;
		a[k] = a[i];
		k = i;

	}
	a[k] = v;
}

int extract(int *a) {
	// get root node and down heap
	int v = a[1];
	a[1] = a[nheap--];
	downheap(a, 1);
	return v;
}

void insert(int *a, int *N, int v)
{
	a[++(*N)] = v;
	upheap(a, *N);
}

void heap_sorting_B(int *a, int N) {
	int k, t;
	a[0] = INT_MAX;
	nheap = N;
	for (k = N / 2; k > 0; k--)
		downheap(a, k);
	while (nheap > 0) {
		if (mode == 1)
			printf("%2d", t = a[1]);
		t = a[1];
		a[1] = a[nheap];
		a[nheap--] = t;
		downheap(a, 1);
	}
}