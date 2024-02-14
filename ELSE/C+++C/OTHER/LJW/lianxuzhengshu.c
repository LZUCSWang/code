#include<stdio.h>
int main(){
    char ch;
    while((ch=getchar())>'9'||ch<'0')if(ch=='\n'){
        printf("%d",0);
        return 0;
    };
    int cntwer=0;
    cntwer+=(ch<='9'&&ch>='1')?ch-'0':0;
    while((ch=getchar())<='9'&&ch>='0'){
        cntwer=cntwer*10+ch-'0';
    }
    printf("%d",cntwer);
}