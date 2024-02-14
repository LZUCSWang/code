#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* qufan(char *inp){
    char *cnt=malloc(strlen(inp));
    for(int i=0;i<strlen(inp);i++){
        cnt[i]=(inp[i]=='0')?'1':'0';
    }
    return cnt;
}
char* he(char *inp1,char *inp2){
    int k=(strlen(inp1)>strlen(inp2)?strlen(inp1):strlen(inp2))-1;
    char *cnt=(char *)malloc(k);
    for(int i=strlen(inp1)-1,j=strlen(inp2)-1;i>=0||j>=0;i--,j--){
        if(i<0)cnt[k--]='0';
        else if(j<0)cnt[k--]='0';
        else if(inp1[i]=='1'&&inp2[j]=='1')cnt[k--]='1';
        else cnt[k--]='0';
    }
    return cnt;
}
char* huo(char *inp1,char *inp2){
    int k=(strlen(inp1)>strlen(inp2)?strlen(inp1):strlen(inp2))-1;
    char *cnt=(char *)malloc(k);
    for(int i=strlen(inp1)-1,j=strlen(inp2)-1;i>=0||j>=0;i--,j--){
        if(i<0)cnt[k--]=inp2[j];
        else if(j<0)cnt[k--]=inp1[i];
        else if(inp1[i]=='1'||inp2[j]=='1')cnt[k--]='1';
        else cnt[k--]='0';
    }
    return cnt;
}
char* yihuo(char *inp1,char *inp2){
    int k=(strlen(inp1)>strlen(inp2)?strlen(inp1):strlen(inp2))-1;
    char *cnt=(char *)malloc(k);
    for(int i=strlen(inp1)-1,j=strlen(inp2)-1;i>=0||j>=0;i--,j--){
        if(i<0)cnt[k--]=inp2[j];
        else if(j<0)cnt[k--]=inp1[i];
        else if(inp1[i]!=inp2[j])cnt[k--]='1';
        else cnt[k--]='0';
    }
    return cnt;
}
int main(){
    char inp1[10],inp2[10];
    scanf("%s %s",inp1,inp2);
    printf("This is ^:%s\nThis is &:%s\nThis is |:%s\nThis is ~:%s %s",yihuo(inp1,inp2),he(inp1,inp2),huo(inp1,inp2),qufan(inp1),qufan(inp2));
}