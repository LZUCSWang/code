int removeElement(int* nums, int numsSize, int val){
    int left=0,right=0;
    while(right<numsSize){
        while(right<numsSize&&nums[right]==val){
            right++;
        }
        while(right<numsSize&&nums[right]!=val){
            nums[left++]=nums[right++];
        }
    }
    return left;
}