#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 101
int main()
{
    int datas[MAX], t, i, j;
    for (i = 0; i < MAX; i++)
    {
        cin >> t;
        if (t == 0)
            break;
        datas[i] = t;
    }
    for (j = i-1; j >= 0; j--)
    {
        cout << datas[j] << " ";
    }
}