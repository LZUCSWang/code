#include<stdio.h>
int missingNumber(int* nums, int numsSize){
    long long int sum=0;
    for(int i=0;i<numsSize;i++){
        sum+=nums[i];
    }
    return numsSize*(numsSize+1)/2-sum;
}
int main(){
    int arr[9]={9,6,4,2,3,5,7,0,1};
    printf("%d",missingNumber(arr,9));

}