#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int datas[MAX];
int n, m;
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &datas[i]);
    }
    while (m--)
    {
        int t;
        scanf("%d", &t);
        int lb = lower_bound(datas, datas + n, t) - datas;
        if (datas[lb] != t)
        {
            printf("-1 ");
        }
        else
        {
            printf("%d ", lb+1);
        }
    }
}