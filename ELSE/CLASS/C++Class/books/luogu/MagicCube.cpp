#include <bits/stdc++.h>
using namespace std;
#define MAX 50
int datas[MAX][MAX] = {0};
int n;
int main()
{
    cin >> n;
    int pos = n / 2;
    int x = 1, y = pos+1;
    datas[x][y] = 1;

    for (int k = 2; k <= n * n; k++)
    {
        if (x == 1 && y != n)
        {
            x = n, y = y + 1;
        }
        else if (x != 1 && y == n)
        {
            x = x - 1, y = 1;
        }
        else if (x == 1 && y == n)
        {
            x = x + 1;
        }
        else if (x != 1 && y != n)
        {
            if (datas[x - 1][y + 1] == 0)
            {
                x = x - 1, y = y + 1;
            }
            else
            {
                x = x + 1;
            }
        }
        datas[x][y] = k;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", datas[i][j]);
        }
        cout << endl;
    }
}