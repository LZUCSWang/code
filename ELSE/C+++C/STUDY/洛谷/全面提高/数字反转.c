#include<stdio.h>
int main(){
    int n,cnt=0;
    scanf("%d",&n);
    while (n){
        cnt+=n%10;
        if (n/10){
            cnt*=10;
        }
        n/=10;
    }
    printf("%d",cnt);
}