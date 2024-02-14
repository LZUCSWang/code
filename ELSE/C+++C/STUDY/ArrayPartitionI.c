#include<stdio.h>
void maopao(int *nums,int numsSize){
    int i,j,t;
    for(i=0;i<numsSize-1;i++)for(j=0;j<numsSize-1-i;j++)if(nums[j]>nums[j+1]){
        t=nums[j];
        nums[j]=nums[j+1];
        nums[j+1]=t;
    }
}
int arrayPairSum(int* nums, int numsSize){
    maopao(nums,numsSize);
    int sum=0;
    for(int i=0;i<numsSize;i+=2){
        sum+=nums[i];
    }
    return sum;
}
int main(){
    int arr[]={1,4,3,2};
    printf("%d",arrayPairSum(arr,4));
}