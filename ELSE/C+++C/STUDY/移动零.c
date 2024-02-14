#include<stdio.h>
void moveZeroes(int* nums, int numsSize){
    int left=0,right=0,t;
    while(right<numsSize){
        if(nums[right]!=0){
            t=nums[right];
            nums[right]=nums[left];
            nums[left]=t;
            left++;
        }
        right++;
    }
}