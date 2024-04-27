/*编写一个函数接受这些参数：内含int类型元素的数组名、数组的大小和一个代表选取次数的值。该函数从数组中随机选择指定数量的元素，并打印它们。
每个元素只能选择一次（模拟抽奖数字或挑选陪审团成员）。另外，如果你的实现有time()
（第12章讨论过）或类似的函数，可在srand()中使用这个函数的输出来初始化随机数生成器rand()。编写一个简单的程序测试该函数。*/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int judge(int x,int *arry,int size){
    for(int i=0;i<size;i++){
        if(x==arry[i])return 1;
    }
    return 0;
}
void suiji(int *arr,int size,int geshu){
    int suiji,arry[size],k=0;
    srand(time(0));
    suiji=rand()%10;
    arry[0]=suiji;
    printf("%d\n",arr[suiji]);
    while(geshu-1>0){
        suiji=rand()%10;
        while(judge(suiji,arry,k+1)==1)suiji=rand()%10;
        printf("%d\n",arr[suiji]);
        arry[++k]=suiji;
        geshu--;
    }
}
int main(){
    int arr[10]={1,2,3,4,5,6,7,8,9,10};
    suiji(arr,10,3);
}