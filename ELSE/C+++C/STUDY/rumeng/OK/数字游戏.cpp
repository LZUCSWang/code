// 4 2
// 4
// 3
// -1
// 2
// https://www.luogu.com.cn/problem/P1043
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2147483647
#define MAX 1000

int big[MAX][MAX][15], small[MAX][MAX][15];

int orign[MAX];
int n, m;
inline int modd(int x)
{
    return (x % 10 + 10) % 10;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        scanf("%d", orign + i), orign[i + n] = orign[i];
    for (int i = 1; i <= 2 * n; i++)
        orign[i] += orign[i - 1];
    for (int i = 1; i <= 2 * n; i++)
        for (int j = i; j <= 2 * n; j++)
            big[i][j][1] = small[i][j][1] = modd(orign[j] - orign[i - 1]);
    for (int sps = 2; sps <= m; sps++)
        for (int left = 1; left <= 2 * n; left++)
            for (int right = left + sps - 1; right <= 2 * n; right++)
                small[left][right][sps] = INF;
    for (int sps = 2; sps <= m; sps++)
        for (int left = 1; left <= 2 * n; left++)
            for (int right = left + sps - 1; right <= 2 * n; right++)
                for (int k = left + sps - 2; k < right; k++)
                    big[left][right][sps] = max(big[left][right][sps], big[left][k][sps - 1] * modd(orign[right] - orign[k])), small[left][right][sps] = min(small[left][right][sps], small[left][k][sps - 1] * modd(orign[right] - orign[k]));
    int max_ans = 0, min_ans = INF;
    for (int i = 1; i <= n; i++)
        max_ans = max(max_ans, big[i][i + n - 1][m]), min_ans = min(min_ans, small[i][i + n - 1][m]);
    cout << min_ans << endl << max_ans;
}