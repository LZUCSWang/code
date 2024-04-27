<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\3\3sortfind.cpp
 * @Description: 选择排序和折半查找，其中使用指针法访问数组
 */

#include <iostream>
using namespace std;
/**
 * @description: 选择排序，使用指针法访问数组
 * @param {int} *p 数组指针
 * @param {int} n  数组长度
 * @return {*}
 */

void sort(int *p, int n)
{
    int i, j, k, t;
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if (*(p + j) > *(p + k))
            {
                k = j;
            }
        }
        t = *(p + i);
        *(p + i) = *(p + k);
        *(p + k) = t;
    }
}

/**
 * @description: 折半查找
 * @param {int} *p 数组指针
 * @param {int} n 数组长度
 * @param {int} x 要查找的数
 * @return {*}
 */
int search(int *p, int n, int x)
{
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (*(p + mid) == x) // 找到
        {
            return mid + 1;
        }
        else if (*(p + mid) > x) // 在左半部分
        {
            low = mid + 1;
        }
        else // 在右半部分
        {
            high = mid - 1;
=======
#include <iostream>
using namespace std;

void selection_sort(int *arr, int n) // 选择排序
{
    for (int i = 0; i < n - 1; i++)
    {
        int max_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[max_idx])
            {
                max_idx = j;
            }
        }
        swap(arr[i], arr[max_idx]);
    }
}

int binary_search(int *arr, int n, int target) // 二分查找
{
    int left = 0, right = n - 1; // 左右指针
    while (left <= right)        // 左右指针相遇时结束循环
    {
        int mid = left + (right - left) / 2; // 中间指针
        if (arr[mid] == target)              // 找到目标值
        {
            return mid; // 返回目标值的下标
        }
        else if (arr[mid] < target) // 目标值在右侧
        {
            left = mid + 1; // 左指针右移
        }
        else // 目标值在左侧
        {
            right = mid - 1; // 右指针左移
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
        }
    }
    return -1;
}
<<<<<<< HEAD
int main()
{
    int a[15], i, x, result;
    for (i = 0; i < 15; i++)
    {
        cin >> a[i];
    }
    sort(a, 15); // 选择排序
    cout << "After sorted:" << endl;
    for (i = 0; i < 15; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl
         << "Input the number you want to search:";
    cin >> x;
    result = search(a, 15, x); // 二分查找
    if (result == -1)
    {
        cout << "Not Found" << endl;
    }
    else
    {
        cout << x << "is the " << result << "in the list" << endl;
=======

int main()
{
    int arr[15];
    cout << "Input 15 numbers: ";
    for (int i = 0; i < 15; i++)
    {
        cin >> arr[i];
    }
    selection_sort(arr, 15);
    cout << "Output sorted numbers:";
    for (int i = 0; i < 15; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    int target;
    cout << "Input target number:";
    cin >> target;
    int idx = binary_search(arr, 15, target);
    if (idx == -1)
    {
        cout << "The Target Number Could Not Be Found" << endl;
    }
    else
    {
        cout << "Target number is at " << idx + 1 << endl;
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    }
    return 0;
}
