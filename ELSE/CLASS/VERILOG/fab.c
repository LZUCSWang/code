// 动态规划求斐波那契前十项
#include <stdio.h>
int main()
{
    int i;
    int a[10];
    a[0] = 1;
    a[1] = 1;
    for (i = 2; i < 4; i++)
    {
        a[i] = a[i - 1] + a[i - 2];
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}