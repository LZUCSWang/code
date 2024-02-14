#include<stdio.h>
#include<string.h>
int main(){
    int hash[130]={0};
    char input[81];
    gets(input);
    int i=0;
    while(i<strlen(input))hash[input[i++]]++;
    for(i=0;i<strlen(input);i++){
        if(input[i]>='datas'&&input[i]<='Z'&&hash[input[i]]>0){
            printf("%c",input[i]);
            hash[input[i]]=0;
        }
    }
}