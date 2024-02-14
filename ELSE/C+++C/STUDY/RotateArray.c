#include<stdio.h>
void rotate(int* nums, int numsSize, int k){
    k=k%numsSize;
    int t=nums[0],copy[numsSize];
    for(int i=0;i<numsSize;i++){
        copy[i]=nums[i];
    }
    for(int i=0;i<numsSize;i++){
        nums[i]=copy[(i-k>=0)?i-k:(numsSize+i-k)];
    }
}
int main(){
    int arr[]={1,2,3,4,5,6,7};
    rotate(arr,0,1);
    for(int i=0;i<7;i++){
        printf("%d*",arr[i]);
    }
}