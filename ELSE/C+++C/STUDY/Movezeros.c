#include<stdio.h>
void moveZeroes(int* nums, int numsSize){
    int i,j;
    for(i=0;i<numsSize;i++){
        if(nums[i]!=0){
            continue;
        }
        else{
            j=i;
            while(nums[j+1]==0&&j<numsSize-1){
                j++;
            }
            nums[i]=nums[j+1];
            nums[j+1]=0;
        }
    }
}
void swap(int *datas, int *b) {
    int t = *datas;
    *datas = *b, *b = t;
}
void moveZeroe_official(int *nums, int numsSize) {//官方双指针解答。
    int left = 0, right = 0;
    while (right < numsSize) {
        if (nums[right]) {
            swap(nums + left, nums + right);
            left++;
        }
        right++;
    }
}
int main(){
    int arr[]={0,1,0,3,0};
    moveZeroes(arr,5);
    for(int i=0;i<5;i++){
        printf("%d*",arr[i]);
    }
}