#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define card_size 1
#define arr_size 100

typedef struct
{
	char name[arr_size];
	char phone[arr_size];
	char department[arr_size];
	// make your code
}namecard; // 전화번호부를 위한 구조체

namecard card[card_size]; // 전화번호부를 위한 구조체 배열

int num = 0; // 현재 전화번호부에 저장된 사람 수.

FILE *fp;

void clearinputbuffer() // 입력 버퍼 클리어
{
	while (getchar() != '\n');
}

int menu() // 화면에 메뉴를 띄우는 함수
{
	int a;
	printf("1. add\n");
	printf("2. search\n");
	printf("3. delete\n");
	printf("4. file write\n");
	printf("5. list view\n");
	printf("6. quit\n");
	printf("Select manu : ");
	scanf("%d", &a);
	clearinputbuffer();

	return a;
}

int add() // 전화번호부에 새로운 사람을 추가하는 함수.
{
	if (num > card_size)
	{
		printf("ERROR!! We cannot make more card\n\n");
		return -1;
	}
	else
	{
		printf("make new person\n");
		printf("name : ");
		scanf("%[^\n]s", card[num].name);
		clearinputbuffer();
		printf("phone : ");
		scanf("%[^\n]s", card[num].phone);
		clearinputbuffer();
		printf("department : ");
		scanf("%[^\n]s", card[num].department);
		clearinputbuffer();

		printf("\n");
		printf("your input : name : %s\n", card[num].name);
		printf("your input : phone : %s\n", card[num].phone);
		printf("your input : department : %s\n", card[num].department);

		num++;
		printf("\n");
	}
}

int search()
{
	int a;
	int fi;
	char str[arr_size];
	int find = 0;
	printf("1. with name\n"); // 이름을 기준으로 전화번호부를 검색한다.
	printf("2. with phone number\n"); // 전화번호를 기준으로 전화번호부를 검색한다.
	printf("3. with department\n"); // 부서를 기준으로 전화번호부를 검색한다.
	printf("Select manu : ");
	scanf("%d", &a);
	clearinputbuffer();
	switch (a)
	{
	case 1:
		printf("\n");
		printf("what is name?");
		scanf("%[^\n]s", str);
		clearinputbuffer();
		for (fi = 0; fi < num; fi++)
		{
			if (!strcmp(str, card[fi].name))
			{
				printf("\n");
				printf("-----------------------------\n");
				printf("card number : %d\n", fi);
				printf("name : %s\n", card[fi].name);
				printf("phone : %s\n", card[fi].phone);
				printf("department : %s\n", card[fi].department);
				find++;
			}
		}
		if (find == 0)
		{
			printf("-----------------------------\n");
			printf("cannot find %s\n", str);
		}
		else
		{
			printf("-----------------------------\n");
			printf("we find %d person\n", find);
		}
		break;
	case 2:
		printf("\n");
		printf("what is phone num?");
		scanf("%[^\n]s", str);
		clearinputbuffer();
		for (fi = 0; fi < num; fi++)
		{
			if (!strcmp(str, card[fi].phone))
			{
				printf("\n");
				printf("-----------------------------\n");
				printf("card number : %d\n", fi);
				printf("name : %s\n", card[fi].name);
				printf("phone : %s\n", card[fi].phone);
				printf("department : %s\n", card[fi].department);
				find++;
			}
		}
		if (find == 0)
		{
			printf("-----------------------------\n");
			printf("cannot find %s\n", str);
		}
		else
		{
			printf("-----------------------------\n");
			printf("we find %d phone num\n", find);
		}
		break;
	case 3:
		printf("\n");
		printf("what is department name?");
		scanf("%[^\n]s", str);
		clearinputbuffer();
		for (fi = 0; fi < num; fi++)
		{
			if (!strcmp(str, card[fi].department))
			{
				printf("\n");
				printf("-----------------------------\n");
				printf("card number : %d\n", fi);
				printf("name : %s\n", card[fi].name);
				printf("phone : %s\n", card[fi].phone);
				printf("department : %s\n", card[fi].department);
				find++;
			}
		}
		if (find == 0)
		{
			printf("-----------------------------\n");
			printf("cannot find %s\n", str);
		}
		else
		{
			printf("-----------------------------\n");
			printf("we find %d department\n", find);
		}
		break;
	default:
		printf("check your command\n");
		break;
	}
	printf("\n");
}

int del()
{
	int i, str=-1;
	// 특정 리스트 번호의 사람을 찾아서 지운다.
	// (전화번호를 검색해서 지우는 것이 아니다. namecard card[card_size]; 배열의 인덱스 번호를 기준으로 지운다.)
	// 지우는 동작은 그 번호 뒤에 있는 데이터들을 앞으로 덮어 쓰는 것으로 구현한다.
	while (1) {
		printf("list num : ");
		scanf("%d", &str);
		clearinputbuffer();
		if (str != -1&&str<num) break;
		else {
			printf("error\n");
		}
	} 
	for (i = str; i < card_size; i++) {
		card[i] = card[i+1];
	}
	num--;
	// make your code
}


int filewrite()
{
	// file을 열어서 그 데이터를 파일에 저장한다.
	// 기존에 있던 파일은 날려도 상관없다.
	// 파일을 열었으면 반드시 닫도록 한다.
	// 파일 이름은 자유.
	// 반드시 텍스트 형식일것.
	int n = 0;
	
	remove("phone_num.txt");

	if (!(fp = fopen("phone_num.txt", "w"))) {
		printf("error\n\n");
		return -1;
	}
	
	for (n = 0; n < num; n++) {
		fputc((char)n+48, fp);
		fputs("\nname : ", fp);
		fputs(card[n].name, fp);
		fputs("\nphone num : ", fp);
		fputs(card[n].phone, fp);
		fputs("\ndepartment : ", fp);
		fputs(card[n].department, fp);
		fputs("\n\n", fp);
	}

	fclose(fp);

	return 0;
	// make your code
}
	
int ls()
{
	// namecard card[card_size];의 모든 값을 화면에 현시한다.
	int fi;
	for (fi = 0; fi < num; fi++)
	{
		printf("name : %s\n", card[fi].name);
		printf("phone : %s\n", card[fi].phone);
		printf("department : %s\n\n", card[fi].department);
	}
}

int main()
{
	while (1)
	{
		switch (menu())
		{
		case 1:
			printf("\n");
			add();
			break;
		case 2:
			printf("\n");
			search();
			break;
		case 3:
			printf("\n");
			del();
			break;
		case 4:
			printf("\n");
			filewrite();
			break;
		case 5:
			printf("\n");
			ls();
			break;
		case 6:
			printf("Quit!!\n");
			return 0;
			break;
		default:
			printf("check your input\n\n");
			break;
		}
	}
}

// 정의 vs 선언
// 헤더파일이 필요한 이유?
// typedef 사용하는 이유는?
// 특정 센서들을 사용하는 방법은?
// 파일 입출력의 명령어들이 가지는 차이점은?
