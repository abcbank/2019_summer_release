    #include<stdio.h>
    #include<stdlib.h>
    #include<time.h>

    int main() {
        int a, b;
        srand((unsigned int)time(NULL));
        //난수 발생함수
        a = rand() % 100 + 1;
        // 발생된 난수를 100으로 나머지 연산을 한 후, 1을 더한다(1~100범위 설정)
        while (1)
        {
            printf("user>>");
            scanf_s("%d", &b);
            //사용자가 변수를 입력받을때 쓰는 함수
            if (a == b) {
            // if 내의 조건이 참이면 내부 명령어 실행
                printf("\t a(%d) = %d\n", a, b);
                break;
            }
            else if (a > b)
            // else if 내의 조건이 참이면 내부 명령어 실행
            {
                printf("\t a > %d\n", b);
            }
            else if (a < b)
            {
                printf("\t a < %d\n", b);
            }
        }
        while (1);
        return 0;
    }