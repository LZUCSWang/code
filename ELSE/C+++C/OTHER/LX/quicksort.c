#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
void quicksort(int *arr, int l, int r)
{
    if (l >= r)
        return;
    //对数组元素进行排序
    int s = arr[l]; // s为分割点。
    int *arr1 = (int *)malloc((r + 1) * sizeof(int));
    int *arr2 = (int *)malloc((r + 1) * sizeof(int));
    int i = 0, mid_inx = 0, len_arr1 = 0, len_arr2 = 0;
    for (i = l; i <= r; i++)
        if (arr[i] <= s)
            arr1[len_arr1++] = arr[i];
        else
            arr2[len_arr2++] = arr[i];
    int idx = l;
    mid_inx = l + len_arr1 - 1;
    for (i = 0; i < len_arr1; i++) //把arr1的元素放回arr左边
        arr[idx++] = arr1[i];
    for (i = 0; i < len_arr2; i++) //把arr2的元素放回arr右边
        arr[idx++] = arr2[i];
    //进行递归处理

    int temp = arr[mid_inx];
    arr[mid_inx] = s;
    arr[l] = temp; //把第一个数，也就是分割点，放到中间
    printf("mid_inx = %d s = %d##", mid_inx, s);
    for (i = l; i <= r; i++)
        printf("%d ", arr[i]);
    putchar('\n'); //输出分块后各自的排序过程，注释掉
    free(arr1);
    free(arr2);
    quicksort(arr, l, mid_inx - 1); //对分割点左边的数组（比分割点小的）进行排序
    quicksort(arr, mid_inx + 1, r); //对分割点右边的数组（比分割点大的）进行排序
}
int main()
{
    int arr[10] = {1, 7, 5, 3, 0, 2, 5, 9, 8, 4};
    int sz = sizeof(arr) / sizeof(arr[0]);
    quicksort(arr, 0, sz - 1);
    for (int i = 0; i < sz; i++)
        printf("%d ", arr[i]);
    return 0;
}
