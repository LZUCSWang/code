#include<stdio.h>
double findMaxAverage(int* nums, int numsSize, int k){
    int i,j,sum=0,max=-9999;
    for(i=0;i<numsSize-k+1;i++,sum=0){
        for(j=i;j<i+k;j++){
            sum+=nums[j];
        }
        max=(max<sum)?sum:max;
    }
    return (double)max/k;
}
int main(){
    int arr[]={1,12,-5,-6,50,3};
    findMaxAverage(arr,6,4);
}