int missingNumber(int* nums, int numsSize){
    int cnt=0;
    for(int i=0;i<numsSize;i++){
        cnt^=nums[i]^(i+1);
    }
    return cnt;
}