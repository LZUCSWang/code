#include<stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize){
    int end=digitsSize-1,flag=0;
    while(digits[end]==9){
        digits[end]=0;
        if(end==0){
            flag=1;
            break;
        }
        end--;
    }
    if(flag==0){
        digits[end]++;
        *returnSize=digitsSize;
        return digits;
    }
    else {
        *returnSize=++digitsSize;
        int *arr=(int *)malloc(sizeof(int)*digitsSize);
        *arr=0;
        return arr;
    }

}