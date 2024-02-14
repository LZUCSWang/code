#include<stdio.h>
#include<stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int getStandard(int array[], int i, int j) {
    // 基准数据
    int key = array[i];
    while (i < j) {
        // 因为默认基准是从左边开始，所以从右边开始比较
        // 当队尾的元素大于等于基准数据 时,就一直向前挪动 j 指针
        while (i < j && array[j] >= key) {
            j--;
        }
        // 当找到比 array[i] 小的时，就把后面的值 array[j] 赋给它
        if (i < j) {
            array[i] = array[j];
        }
        // 当队首元素小于等于基准数据 时,就一直向后挪动 i 指针
        while (i < j && array[i] <= key) {
            i++;
        }
        // 当找到比 array[j] 大的时，就把前面的值 array[i] 赋给它
        if (i < j) {
            array[j] = array[i];
        }
    }
    // 跳出循环时 i 和 j 相等,此时的 i 或 j 就是 key 的正确索引位置
    // 把基准数据赋给正确位置
    array[i] = key;
    return i;
}

void QuickSort(int array[], int low, int high) {
    // 开始默认基准为 low
    if (low < high) {
        // 分段位置下标
        int standard = getStandard(array, low, high);
        // 递归调用排序
        // 左边排序
        QuickSort(array, low, standard - 1);
        // 右边排序
        QuickSort(array, standard + 1, high);
    }
}
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    QuickSort(nums1,0,nums1Size-1);
    QuickSort(nums2,0,nums2Size-1);
    int i,j,k=0,min=((nums1Size>nums2Size)?nums2Size:nums1Size);
    int *arr=(int*)malloc(sizeof(int)*min);
    while(1){
        if(i==nums1Size||j==nums2Size)break;
        if(nums1[i]==nums2[j]){
            arr[k++]=nums2[i];
            *returnSize++;
        }
        else if(nums1[i]>nums2[j]){
            j++;
        }
        else {
            i++;
        }
    }
    return arr;

}