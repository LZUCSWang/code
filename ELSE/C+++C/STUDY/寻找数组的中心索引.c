int pivotIndex(int* nums, int numsSize){
    int left_sum=0,right_sum=0;
    for(int i=0;i<numsSize;i++){
        right_sum+=nums[i];
    }
    for(int i=0;i<numsSize;i++){
        if(i==0){
            right_sum-=nums[i];
            if(left_sum==right_sum)return 0;
        }
        left_sum+=nums[i-1];
        right_sum-=nums[i];
        if(left_sum==right_sum)return i;
    }
    return -1;
}