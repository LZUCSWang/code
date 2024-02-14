#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
// https://www.luogu.com.cn/problem/P5020
int t, n;
int flag[MAX], coin[MAX];
int main()
{
    cin >> t;
    while (t--)
    {
        memset(flag, 0, sizeof(flag));
        memset(coin, 0, sizeof(coin));
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", coin + i);
            flag[coin[i]] = 2;
        }
        sort(coin + 1, coin + n + 1);
        for (int i = 1; i <= coin[n]; i++)
            if (flag[i])
                for (int j = 1; j <= n; j++)
                    if (i + coin[j] <= coin[n])
                        flag[i + coin[j]] = 1;
                    else
                        break;
        int ans = 0;
        for (int i = 1; i <= coin[n]; i++)
        {
            if (flag[i] == 2)
                ans++;
        }
        printf("%d\n", ans);
    }
}