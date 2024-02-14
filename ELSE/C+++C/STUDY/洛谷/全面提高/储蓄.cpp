#include<bits/stdc++.h>
// int yusuan[13];
int main(){
    int rest=0;
    int temp;
    int cnt=0;
    for ( int i =1;i<=12;i++){
        scanf("%d",&temp);
        rest+=300;
        rest-=temp;
        if (rest<0){
            printf("%d\n",-i);
            return 0;
        }
        cnt+=(rest/100)*100;
        rest%=100;
    }
    printf("%.0f",(rest)+cnt*1.2);
}