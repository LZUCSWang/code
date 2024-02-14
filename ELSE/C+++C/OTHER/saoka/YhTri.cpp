// #include "stdafx.h"
#include <iostream>
using namespace std;
void yhTri(int a[][10], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j == 0 || j == i)
                a[i][j] = 1;
            else
                a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
    }
}

int main()
{
    int a[10][10];
    int n;
    cout << "n=";
    cin >> n;
    cout << "YhTri:" << endl;
    yhTri(a, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << "\n";
    }
    return 0;
}
