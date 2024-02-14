#include<stdio.h>
int jiechen(int n){
    int sum=1;
    for(int i=1;i<=n;i++){
        sum*=i;
    }
    return sum;
}
int c(int m,int n){
    return (jiechen(m)/(jiechen(n)*jiechen(m-n)));
}
int main(){
    printf("%d",c(1,1));
}