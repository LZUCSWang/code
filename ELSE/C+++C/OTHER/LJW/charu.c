#include<stdio.h>
int main(){
    int len,arr[11],target;
    scanf("%d",&len);
    for(int i=0;i<len;i++){
        scanf("%d",&arr[i]);
    }
    scanf("%d",&target);
    for(int i=0;i<len;i++){
        if(target<arr[i]){//如果找到值
            for(int j=len;j>i;j--){//从最后一位开始，每一位和前面的一位相等，就是将第i个之后的向后移，其中i的值给到i+1
                arr[j]=arr[j-1];
            }
            arr[i]=target;//最后将target给到i位置
            break;
        }
    }
    for(int i=0;i<len+1;i++){
        printf("%d ",arr[i]);
    }
}