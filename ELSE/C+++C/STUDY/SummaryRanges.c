#include<stdio.h>
#include<string.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** summaryRanges(int* nums, int numsSize, int* returnSize){
    int i=0,low,high,*returnSize=0;
    char** ret=malloc(numsSize*sizeof(char *));
    while(i<numsSize){
        low=i;
        i++;
        while(i<numsSize&&nums[i]==nums[i-1]+1){
            i++;
        }
        high=i-1;
        char* temp=malloc(sizeof(char)*25);
        sprintf(temp,"%d",nums[low]);
        if(low<high){
            sprintf(temp,"->");
            sprintf(temp,"%d",nums[high]);
        }
        ret[(*returnSize)++]=temp;
    }
    return ret;
}