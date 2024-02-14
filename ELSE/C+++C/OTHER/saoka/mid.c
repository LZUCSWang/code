#include <stdio.h>
int main()
{
    int a[15];
    int i, j, n, mid, sign = 0;
    printf("请输入要存储的15个数：\n");
    for (i = 0; i < 15; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("\n请输入要查找的一个数：");
    scanf("%d", &n);
    i = 0;
    j = 14;
    while (i <= j)
    {
        mid = (i + j) / 2;
        if (a[mid] > n)
        {
            j = mid - 1;
        }
        if (a[mid] < n)
        {
            i = mid + 1;
        }
        if (a[mid] == n)
        {
            printf("该数是第%d个元素", mid + 1);
            sign = 1;
            break;
        }
    }
    if (sign == 0)
        printf("无此数！");
}
