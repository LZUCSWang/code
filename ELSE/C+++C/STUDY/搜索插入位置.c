#include<stdbool.h>
int searchInsert(int* nums, int numsSize, int target){
    int left=0,right=numsSize-1;
    int mid;
    while(left<=right){
        mid=left+(right-left)/2;
        if(nums[mid]==target)return mid;
        else if(nums[mid]>target)right=mid-1;
        else if(nums[mid]<target)left=mid+;
    }
    return left;
}