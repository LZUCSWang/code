#include<stdio.h>
int singleNumber(int* nums, int numsSize){
    if(numsSize==1)return nums[0];
    for(int i=0;i<numsSize;i++){
        for(int j=i+1;j<numsSize;j++){
            if(nums[i]==nums[j]){
                nums[i]=nums[j]='*';
                break;
            }
        }
    }
    for(int i=0;i<numsSize;i++){
        if(nums[i]!='*')return nums[i];
    }
    return 0;
}
int main(){
    int arr[]={4,3,3,2,2,1,4};
    printf("%d",singleNumber(arr,7));
}