#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

void HighPlus(char x1[], char x2[])
{
    int i, j, n, n1 = strlen(x1), n2 = strlen(x2);
    int a[N] = {0}, b[N] = {0};
    for (i = n1 - 1, j = 0; i >= 0; i--)
        a[j++] = x1[i] - '0'; //字符转整数
    for (i = n2 - 1, j = 0; i >= 0; i--)
        b[j++] = x2[i] - '0'; //字符转整数
    if (n1 > n2)
        n = n1;
    else //取高位数
        n = n2;
    for (i = 0; n > i; i++)
    {
        a[i] += b[i];
        a[i + 1] += a[i] / 10; //按位做加法
        a[i] = a[i] % 10;
    }
    if (a[n] != 0)
        n = n + 1; //如果最高位进位，位数加一
    // Output(a, n);
}

void HighMultiply(char x1[], char x2[])
{
    int i, j = 0, n, n1 = strlen(x1), n2 = strlen(x2);
    int a[N] = {0}, b[N] = {0}, c[1000] = {0};
    for (i = n1, j = 1; i >= 1; i--)
        a[j++] = x1[i - 1] - '0'; //字符转整数
    for (i = n2, j = 1; i > 0; i--)
        b[j++] = x2[i - 1] - '0'; //字符转整数
    for (i = 1; n1 >= i; i++)
    {
        for (j = 1; n2 >= j; j++)
        {
            c[i + j - 1] += a[i] * b[j]; //按位乘，同时错位相加
            c[i + j] += c[i + j - 1] / 10;
            c[i + j - 1] %= 10;
        }
    }
    n = i + j;
    while (c[n] == 0 && n > 1)
        n--; //除首位0
    for (i = n; i >= 1; i--)
    {
        printf("%d", c[i]);
    }
}

int main()
{
    char x1[N], x2[N];
    scanf("%s%s", x1, x2);
    HighMultiply(x1, x2);
    return 0;
}