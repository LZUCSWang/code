#include<stdio.h>
#include<string.h>
int change(char* datas){
    int sum=0;
    for(int i=strlen(datas)-1;i>=0;i--){
        if(datas[i]=='1')sum=sum*2+1;
        else sum=sum*2;
    }
    return sum;
}
int main(){
    char input[10];
    scanf("%s",input); 
    printf("%d",change(input));
}