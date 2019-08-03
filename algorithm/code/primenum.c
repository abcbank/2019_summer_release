#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//get prime number -> 가장 큰 두수의 곱까지
//가장 큰 소수와 가장 작은 소수라 가정.
//만들수 있는지 확인
typedef struct number{
    int *num;
    int size;
}number;
int main(void){
    number input;
    int output; 
    printf("size : ");
    scanf("%d",&(input.size));
    input.num=(int*)calloc(input.size, sizeof(int));
    for(int n=0; n<input.size; n++){
        printf("%d member : ", n+1);
        scanf("%d", input.(num+n));
    }
    

}
