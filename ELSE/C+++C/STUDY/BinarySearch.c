#include<stdio.h>
int search(int* nums, int numsSize, int target){
    int mid,left=0,right=numsSize-1;
    while(left<=right){
        mid=(left+right)/2;
        if(nums[mid]==target)return mid;
        else if(nums[mid]>target)right=mid-1;
        else left=mid+1;
    }
    return -1;
}
int main(){
    int arr[]={1,2,3,4,5,6};
    int datas;
    scanf("%d",&datas);
    printf("%d",search(arr,6,datas));
}