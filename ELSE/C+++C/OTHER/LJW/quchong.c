#include<stdio.h>
#include<string.h>
int main(){
    int hash[130]={0};
    char input[81];
    gets(input);
    for(int i=0;i<strlen(input);i++){
        hash[input[i]]++;
    }
    for(int i=0;i<130;i++){
        if(hash[i]>0)printf("%c",i);
    }
}