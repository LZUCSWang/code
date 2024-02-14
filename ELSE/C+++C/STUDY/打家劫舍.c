#include<stdio.h>
int rob(int* nums, int numsSize){
    if(numsSize==0)return 0;
    if(numsSize==1)return nums[0];
    if(numsSize==2)return (nums[0]>nums[1])?nums[0]:nums[1];
    int arr[numsSize];
    int datas,b;
    arr[0]=nums[0],arr[1]=(nums[0]>nums[1])?nums[0]:nums[1];
    for(int i=2;i<numsSize;i++){
        datas=arr[i-1];
        b=arr[i-2]+nums[i];
        arr[i]=(datas>b)?datas:b;
    }
    int max=0;
    for(int i=0;i<numsSize;i++){
        max=(max<arr[i])?arr[i]:max;
    }
    return max;
}