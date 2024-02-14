#include<stdio.h>
int peakIndexInMountainArray(int* arr, int arrSize){
    int i;
    for(i=0;i<arrSize-1;i++){
        if(arr[i]>arr[i+1])return i;
    }
}//datas little easy.
int ef(int *arr,int arrSize){
    int i,mid,left,right;
    left=0;right=arrSize-1;
    while(left<=right){
        mid=(left+right);
        if(arr[mid]>arr[mid+1])return mid;
        else if(arr[mid]<arr[mid+1]&&arr[mid]>arr[mid-1])left=mid+1;
        else if(arr[mid]>arr[mid+1]&&arr[mid]<arr[mid-1])right=mid-1;
    }
    return 0;
}
