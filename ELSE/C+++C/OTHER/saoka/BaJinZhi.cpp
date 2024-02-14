// #include "stdafx.h"
#include <iostream>
using namespace std;
int n, a[100], i;
void transform(int b)
{
    if (b == 0)
        // cout << "error";
        return;
    else
    {
        transform(b / 8);
        a[++i] = b % 8;
    }
}
int main()
{
    cout << "请输入一个整数：";
    cin >> n;
    transform(n);
    cout << "转换八进制后为：";
    for (int j = 1; j <= i; j++)
        cout << a[j];
}
//