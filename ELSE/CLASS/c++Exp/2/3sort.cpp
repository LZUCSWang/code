<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\2\3sort.cpp
 * @Description: 选择排序和折半查找
 */
#include <iostream>
using namespace std;

/**
 * @description: 实现选择排序
 * @param {int} arr 数组
 * @param {int} n   数组长度
 * @return {*}
 */
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) // 从0开始，到n-1
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) // 从i+1开始，到n
        {
            if (arr[j] < arr[minIndex]) // 如果arr[j]比arr[minIndex]小
            {
                minIndex = j; // 更新minIndex
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

/**
 * @description: 实现折半查找
 * @param {int} arr 折半查找的数组
 * @param {int} n   数组长度
 * @param {int} target  要查找的目标
 * @return {*} 返回目标的下标，如果没有找到，返回-1
 */
int binarySearch(int arr[], int n, int target)
{
    int left = 0, right = n - 1;
    while (left <= right) // 如果left大于right，说明没有找到
    {
        int mid = left + (right - left) / 2; // 防止溢出
        if (arr[mid] == target)              // 如果找到了
        {
            return mid; // 返回下标
        }
        else if (arr[mid] < target) // 如果目标比中间值大
        {
            left = mid + 1; // 更新left
        }
        else
        {
            right = mid - 1; // 更新right
        }
    }
    return -1;
=======
#include <iostream>
using namespace std;

void selectionSort(int arr[], int n)
{
    // ????????��????????��?????????????????
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i; // ?????��?????????
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]); // ????��??????????????
    }
}

// ?????????
int binarySearch(int arr[], int n, int target)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
        {
            return mid; // ??????????????????
        }
        else if (arr[mid] < target)
        {
            left = mid + 1; // ??????????????????????
        }
        else
        {
            right = mid - 1; // ??????????????????????
        }
    }
    return -1; // ?????????????????-1
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
}

int main()
{
<<<<<<< HEAD
    const int n = 15;
    int arr[n];
    int score;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if (arr[i] < 0 || arr[i] > 100) // 如果输入的数据不在0到100之间
        {
            cout << "Input error, the input data should be between 0 and 100" << endl;
            i--;
            continue;
        }
    }

    selectionSort(arr, n);

    cout << "sorted array:";
    for (int i = 0; i < n; i++) // 输出排序后的数组
=======
    const int n = 15; // ????i????????????
    int arr[n];       // ????????????????
    int score;        // ???????????????????

    // ????15????????
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        // ?��?????????????
        if (arr[i] < 0 || arr[i] > 100)
        {
            cout << "???????" << endl;
            return 0;
        }
    }

    // ?????????????????
    selectionSort(arr, n);

    // ?????????
    cout << "?????????";
    for (int i = 0; i < n; i++)
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    {
        cout << arr[i] << " ";
    }
    cout << endl;

<<<<<<< HEAD
    cout << "Input the score you want to search:";
    cin >> score;

    int index = binarySearch(arr, n, score); // 查找score的下标

    if (index == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "The position is " << index + 1 << endl;
=======
    // ????????????
    cout << "????????????????";
    cin >> score;

    // ???????????????????????
    int index = binarySearch(arr, n, score);

    // ????????????????????
    if (index == -1)
    {
        cout << "?????" << endl;
    }
    else
    {
        cout << "?��?????????��??" << index + 1 << "???????" << endl;
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    }

    return 0;
}
