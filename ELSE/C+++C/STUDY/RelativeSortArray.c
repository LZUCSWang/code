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
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize){
    *returnSize=arr1Size;
    int i,j,k=0;
    int *arrcnt=(int*)malloc(sizeof(int)*arr1Size);
    for(i=0;i<arr2Size;i++){
        for(j=0;j<arr1Size;j++){
            if(arr1[j]==arr2[i]){
                arrcnt[k++]=arr2[i];
                arr1[j]='*';
            }
        }
    }
    int arr3[arr1Size-k+2],l=0;
    for(i=0;i<arr1Size;i++){
        if(arr1[i]!='*'){
        arr3[l++]=arr1[i];}
    }
    QuickSort(arr3,0,arr1Size-k-1);
    for(i=0;k<arr1Size;i++,k++){
        arrcnt[k]=arr3[i];
    }
    return arrcnt;
}
int main(){
    int arr1[]={2,3,1,3,2,4,6,7,9,2,19},arr2[]={2,1,4,3,9,6};
}