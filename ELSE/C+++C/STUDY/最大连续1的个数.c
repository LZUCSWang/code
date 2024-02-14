
int findMaxConsecutiveOnes(int* nums, int numsSize){
    int count=0,max=0,ptr=0;
    while(ptr<numsSize){
        if(nums[ptr]==1){
            count++;
        }
        else {
            max=(max<count)?count:max;
            count=0;
        }
        ptr++;
    }
    return (max>count)?max:count;
}