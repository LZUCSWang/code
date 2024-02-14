#include<stdio.h>
struct stack{
    char ch[10];
    int i;
};
int main(){
    char input[100],c;
    struct stack s1,s2;
    s1.i=0;
    printf("Printf the string:\n");
    while(scanf("%c",&c)==1&&c!='\n'){
        s1.ch[s1.i]=c;
        s1.i++;
    }
    while(s1.i>=0){
        printf("%c",s1.ch[s1.i-1]);
        s1.i--;
    }
}