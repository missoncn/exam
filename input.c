#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main(){
    char arr[100];
    fgets(arr,sizeof(arr),stdin);
    printf(arr);
}