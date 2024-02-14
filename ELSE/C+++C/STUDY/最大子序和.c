int maxSubArray(int* nums, int numsSize){
    int arr[numsSize];
    int max=-999999999;
    arr[0]=nums[0];
    for(int i=1;i<numsSize;i++){
        arr[i]=(arr[i-1]>0)?arr[i-1]:0+nums[i];
    }
    for(int i=0;i<numsSize;i++){
        if(max<arr[i])max=arr[i];
    }
    return max;
}