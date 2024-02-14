/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include<stdio.h>
#include<stdlib.h>
int* twoSum(int* numbers, int numbersSize, int target){
    int i,j,flag=0;
    for(i=0;i<numbersSize-1;i++){
        for(j=i+1;j<numbersSize;j++){
            if(numbers[i]+numbers[j]==target){
                flag=1;
                break;
            }
        }
        if(flag==1)break;
    }
    int *set;
    set=(int*)malloc(2*sizeof(int));
    set[0]=i;
    set[1]=j;
    return set;
}
int main(){
    int arr[4]={2,7,11,15};
    for(int i=0;i<2;i++){
        printf("%d",twoSum(arr,4,9)[i]);
    }
}