#include<stdio.h>
#include<math.h>
int main(){
    int i,n;
    float e;
    n=i=e=1;
    do{
        n=n*i;
        e=1.0/n+e;
        i++;
    }while (fabs(1.0/n)>=1e-6);
    printf("%d",i);
}