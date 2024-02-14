#include<stdio.h>
int thirdMax(int* nums, int numsSize){
    int max=-99999999,mid=-9999999,third=-99999999;
    for(int i=0;i<numsSize;i++){
        if(max<nums[i]){
            third=mid;
            mid=max;
            max=nums[i];
        }
    }
    return third;
}
int main(){
    int arr[5]={1,2,2,4,5};
    printf("%d",thirdMax(arr,5));
}