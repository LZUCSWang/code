#include <bits/stdc++.h>
using namespace std;
#define MAX 100000010
int n, m;
bool flag[MAX];
int ans[6000010];
int indexs;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 2; i < n; i++)
    {
        if (!flag[i])
            ans[++indexs] = i;
        for (int j = 1; j <= indexs && i * ans[j] <= n; j++)
        {
            flag[i * ans[j]] = true;
            if (i % ans[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int t;
        scanf("%d", &t);
        printf("%d\n", ans[t]);
    }
}