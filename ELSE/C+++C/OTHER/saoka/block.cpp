#include <stdio.h>
#include <map>
#define MAX 1000
#define BLOCK 3
int len = 0;
using namespace std;
void insert(int a[], int point, int data)
{
    if (a[point] > data) // 说明 插入值该插入到其前面
    {
        for (int i = len - 1; i >= point; i--)
        {
            a[i + 1] = a[i]; // 向后移动一个 单位 (原point位置的值也向后移动)
        }
        a[point] = data; // 目标值插入到point位置
    }
    else // 如果大于等于其值就 插入到目标点 后面
    {
        for (int i = len - 1; i > point; i--)
        {
            a[i + 1] = a[i]; // 向后移动一个 单位 (原point位置的值也向后移动)
        }
        a[point + 1] = data; // 目标值插入到point位置
    }
}
void BinarySearch(int a[], int low, int high, int data)
{
    if (low == high) // 找到 插入点
    {
        insert(a, low, data); // 参数:数组，插入点，插入数据
        return;
    }
    int mid = (low + high) / 2; // 获取 中间值

    if (a[mid] < data) // mid小于data 递增有序表中说明 得插入在是在mid的右边
    {
        BinarySearch(a, mid + 1, high, data);
    }
    else if (a[mid] > data) // mid大于data 递增有序表中说明 得插入在mid的左边
    {
        BinarySearch(a, low, mid - 1, data);
    }
    else // 如果存在和插入值一样大的数 直接插入
    {
        insert(a, mid, data); // 参数:数组，插入点，插入数据
        return;
    }
    return;
}
map<int, int> I;
int BlockFind(int n, int arr[], int value)
{
    int number;
    if (n % BLOCK == 0)
        number = n / BLOCK;
    else
        number = (n / BLOCK) + 1;
    for (int i = 0; i < BLOCK; i++)
        I[i] = arr[(i + 1) * number - 1];
    int low = 0, high = BLOCK - 1, mid, i;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (I[mid] >= value)
            high = mid - 1;
        else
            low = mid + 1;
    }
    i = (high + 1) * number;
    while (i < (high + 2) * number && arr[i] != value && i < len) // i < arr.length是为了防止最后一组越界
        i++;
    if (i < (high + 2) * number)
        return i;
    else
        return -1;
}
void print(int *aa)
{
    for (int i = 0; i < len; i++)
        printf("%d ", aa[i]);
    printf("\n");
}
int main()
{
    int aa[MAX], choice = 1;
    printf("Input the length\n");
    scanf("%d", &len);
    printf("Input the arry\n");
    for (int i = 0; i < len; i++)
        scanf("%d", aa + i);
    while (choice != 0)
    {

        printf("Input your choice (1 for insert,2 for search,3 for show,0 for exit)\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Input the num you want to insert\n");
            int data;
            scanf("%d", &data);
            BinarySearch(aa, 0, len - 1, data);
            len++;
        }
        else if (choice == 2)
        {
            printf("Input the nums you want to search\n");
            int key;
            scanf("%d", &key);
            int ans = BlockFind(len, aa, key) + 1;
            if (ans == 0)
                printf("Not found\n");
            else
                printf("Found at %d\n", ans);
        }
        else if (choice == 3)
        {
            print(aa);
        }
    }
    return 0;
}