#include<stdio.h>
int myAtoi(char * s){
    int flag=1,x=1;
    double temp=0;
    for(int i=0;i<strlen(s);i++){
        if(flag==1&&s[i]==' ')continue;
        if(s[i]=='-'&&flag==1){
            x=-1;
            continue;
        }
        if(s[i]=='+'&&flag==1){
            x=1;
            continue;
        }
        if(s[i]>'9'||s[i]<'0')break;
        flag=0;
        temp=temp*10+s[i]-'0';
        if(temp>2147483647){
            return x==1?2147483647:-2147483648;
        } 
    }
    return (int)(x*temp);
}