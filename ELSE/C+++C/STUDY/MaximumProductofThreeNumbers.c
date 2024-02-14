#include<stdio.h>
int maximumProduct(int* nums, int numsSize){
    if(numsSize==3)return nums[0]*nums[1]*nums[2];
    else {
        if(nums[0]>=0)return nums[1]*nums[2]*nums[3];
        else if(nums[numsSize-1]==0)return 0;
        else if(nums[numsSize-1]<0)return nums[numsSize-1]*nums[numsSize-2]*nums[numsSize-3];
        else return ((nums[numsSize-1]*nums[0]*nums[1])>(nums[numsSize-1]*nums[numsSize-2]*nums[numsSize-3])?(nums[numsSize-1]*nums[0]*nums[1]):(nums[numsSize-1]*nums[numsSize-2]*nums[numsSize-3]));
    }
    return 0;
}
int main(){

}