//编写一个函数，接受一个 int 类型的参数，并返回该参数中打开位的数量。在一个程序中测试该函数。
#include<stdio.h>
int countwei(int input){
    int count=0;
    while(1){
        if(input==0)return count;
        count++;input=input>>1;
    }
}
int main(){
    int datas;
    scanf("%d",&datas);
    printf("%d",countwei(datas));
}