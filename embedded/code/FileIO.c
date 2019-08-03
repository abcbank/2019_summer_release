#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10000

int main(void){
    FILE * file=fopen("/file/test.txt","wt");
    char *a="helloworld";
    char *str;
    if(file == NULL)
        printf("파일이 존재하지 않습니다\n");
    else 
        fprintf(file,"%s\n",a);
    fputc(20190313,file);
    while(fgets(str,MAX,file)!=NULL){
        printf("%s",str);
    }
    printf("\n");
    fscanf(file,"%s",str);
    printf("%d\n",str);
    fclose(file);
}