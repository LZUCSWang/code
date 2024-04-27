//编写一个程序，接受两个int类型的参数：一个是值；一个是位的位置。如果指定位的位置为1，该函数返回1；否则返回0。在一个程序中测试该函数。
#include<stdio.h>
int judge(int num,int wei){
    num=num>>(wei-1);
    return num%2;
}
int main(){
    int num,wei;
    scanf("%d %d",&num,&wei);
    printf("%d",judge(num,wei));
}