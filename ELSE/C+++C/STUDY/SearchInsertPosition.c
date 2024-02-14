#include<stdio.h>
int searchInsert(int* nums, int numsSize, int target){
    int i;
    for(i=0;i<numsSize;i++){
        if(target==nums[i])return i;
        else if(target>nums[i]&&target>nums[i+1]&&i<numsSize-1)continue;
        else if(target>nums[i]&&target<nums[i+1]&&i<numsSize-1)return i+1;
    }
    return i;
}
int main(){
    int arr[]={1,3,5,6};
    printf("%d",searchInsert(arr,4,7));
}