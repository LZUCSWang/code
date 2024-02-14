#include<stdio.h>
/*错到拉力。要连续的，快排之后就不连续了int minSubArrayLen(int target, int* nums, int numsSize){
    if(numsSize==1)return (nums[0]==target)?1:0;
    quicksort(nums,0,numsSize-1);
    for(int i=0;i<numsSize;i++){
        printf("%d*",nums[i]);
    }
    int ptr=numsSize-1,sum=0;
    for(;sum<target;ptr--){
        if(ptr<0)return 0;
        sum+=nums[ptr];
    }
    return numsSize-ptr-1;
}*/
int minSubArrayLen(int target, int* nums, int numsSize){
    int quick=0,low=0,cnt=numsSize+1,sum=0;
    for(;quick<numsSize;quick++){
        sum+=nums[quick];
        if(sum>=target){
            while(1){
                if(sum-nums[low]>=target)sum-=nums[low++];
                else break;
            }
            if(cnt>quick-low+1)cnt=quick-low+1;
        }
    }
    return (cnt>numsSize)?0:cnt;
}
int main(){
    int arr[]={12,28,83,4,25,26,25,2,25,25,25,12};
    printf("%d",minSubArrayLen(213,arr,12));
}