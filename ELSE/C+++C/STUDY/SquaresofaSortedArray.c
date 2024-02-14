#include<stdio.h>
#include<stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
    void maopao(int *num,int len){
        int i,j,t;
        for (i=0;i<len-1;i++){
            for(j=0;j<len-i-1;j++){
                if(num[j]>num[j+1]){
                    t=num[j];
                    num[j]=num[j+1];
                    num[j+1]=t;
                }
            }
        }
    }
int* sortedSquares(int* nums, int numsSize,int *returnsize){
    int *res=(int*)malloc(sizeof(int)*numsSize);
    *returnsize=numsSize;
    for(int i=0;i<numsSize;i++)nums[i]=nums[i]*nums[i];
    maopao(nums,numsSize);
    return res;
}
int main(){
    int arr[]={0,-7,-3,2,3,11,12};  
    for(int i=0;i<6;i++){
        printf("%d\n",sortedSquares(arr,6,6)[i]);
    }

}