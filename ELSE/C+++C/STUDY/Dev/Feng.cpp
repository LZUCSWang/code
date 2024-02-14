#include<bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10 , M = 5e1 + 10;
const int inf = 0x3f3f3f3f;
int n, m;
int w[N], s[N];
int f[N][N][M], f1[N][N][M];
int st[N], tp, p;
void insert(int i, int j, int k)
{
    while(tp >= p && f[st[p]][j][k] >= f[i][j][k]) tp--;
    st[++ tp] = i;
}
int solve(int mi)
{
    int ans = inf;
    memset(f, inf, sizeof(f));
    memset(f1, inf, sizeof(f1));
    f[0][0][0] = f1[0][0][0] = 0;
    for (int i = 1; i <= n; i++) f1[0][i][0] = 0;
    for (int k = 1; k <= m; k++) {
        int p1 = -1;
        for (int i = 1; i <= n; i++) {
            int pos = upper_bound(s + 1, s + i + 1, s[i] - mi) - s - 1;
            tp = 0;
            p = 1;
            for (int j = 0; j <= i; j++) {
                if (pos < j) {
                    f[i][j][k] = max(f1[j][pos][k - 1], s[i] - s[pos]);
                } else {
                    f[i][j][k] = max(f1[j][j][k - 1], s[i] - s[j]);
                    while (p1 < pos) insert(++p1, j, k);
                    while (p + 1 <= tp && max(f[st[p]][j][k], s[i] - s[st[p]]) >= max(f[st[p + 1]][j][k], s[i] - s[st[p + 1]])) p ++;
                    int ma = max(f[st[p]][j][k], s[i] - s[st[p]]);
                    f[i][j][k] = min(ma , f[i][j][k]);
                }
                if(s[i] < mi) f[i][j][k] = inf;
                f1[i][j][k] = min(f1[i][j - 1][k], f[i][j][k]);
                if (i == n && k == m) ans = min(ans, f[i][j][k] - mi);
            }
        }
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0) , cout.tie(0);
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i ++){
        cin >> w[i];
        s[i] = s[i - 1] + w[i];
    }
    int res = inf;
    for(int mi = 1; mi * m <= 2 * s[n]; mi++) res = min(res, solve(mi));
    cout << res << '\n';
    return 0;
}
