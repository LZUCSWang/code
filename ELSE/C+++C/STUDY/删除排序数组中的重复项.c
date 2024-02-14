#include<stdio.h>
void swap(int *datas,int *b){
    int t;
    t=*datas,*datas=*b,*b=t;
}
int removeDuplicates(int* nums, int numsSize){
    int left,right;
    left=right=0;
    while(right<numsSize){
        if(nums[left]!=nums[right]){
            left++;
            swap(nums+left,nums+right);
        }
        right++;
    }
}