#include<stdio.h>
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    int i,j;
    for(i=m,j=0;i<nums1Size;i++,j++){
        nums1[i]=nums2[j];
    }
    for(int i=0;i<nums1Size-1;i++){
        for(int j=0;j<nums1Size-i-1;j++){
            if(nums1[j]>nums1[j+1]){
                int t;
                t=nums1[j];
                nums1[j]=nums1[j+1];
                nums1[j+1]=t;
            }
        }
    }
}
int main(){
    int n1[5]={1,2,3},n2[]={2,3};
    merge(n1,5,3,n2,2,2);
    for(int i=0;i<5;i++){
        printf("%d*",n1[i]);
    }
}