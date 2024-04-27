#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, m;
#define MAX_INT 0x3f3f3f3f
int datas[1005][1005];
void input()
{
    cin >> n >> m;
    memset(datas, MAX_INT, sizeof(datas));
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        datas[a][b] = c;
    }
}