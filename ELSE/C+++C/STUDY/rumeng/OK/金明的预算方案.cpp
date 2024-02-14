#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 100000
// https://www.luogu.com.cn/problem/P1064
int n, m;
int main_wei[MAX], main_val[MAX], cnt[MAX], fu_wei[MAX][3], fu_val[MAX][3];
int main()
{
    cin >> n >> m;
    for (int i = 1, a, b, c; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        if (!c)
        {
            main_wei[i] = a;
            main_val[i] = a * b;
        }
        else
        {
            cnt[c]++;
            fu_wei[c][cnt[c]] = a;
            fu_val[c][cnt[c]] = a * b;
        }
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= m; i++)
    {
        for (int j = n; j >= main_wei[i]; j--)
        {
            cnt[j] = max(cnt[j], cnt[j - main_wei[i]] + main_val[i]);
            if (j >= main_wei[i] + fu_wei[i][1])
                cnt[j] = max(cnt[j], cnt[j - main_wei[i] - fu_wei[i][1]] + main_val[i] + fu_val[i][1]);
            if (j >= main_wei[i] + fu_wei[i][2])
                cnt[j] = max(cnt[j], cnt[j - main_wei[i] - fu_wei[i][2]] + main_val[i] + fu_val[i][2]);
            if (j >= main_wei[i] + fu_wei[i][1] + fu_wei[i][2])
                cnt[j] = max(cnt[j], cnt[j - main_wei[i] - fu_wei[i][1] - fu_wei[i][2]] + main_val[i] + fu_val[i][1] + fu_val[i][2]);
        }
    }
    printf("%d", cnt[n]);
}