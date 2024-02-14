#include<stdio.h>
void swap(int *datas,int*b){
    int t=*datas;
    *datas=*b;
    *b=t;
}
int main(){
    int datas=2,b=3;
    swap(&datas,&b);
    printf("%d %d",datas,b);
}