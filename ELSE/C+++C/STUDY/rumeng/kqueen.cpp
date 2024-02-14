#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
struct node
{
    int x, y;
} queens[MAX];
int hang[MAX], lie[MAX];
int n, m, k, ans;
void input()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d", &queens[i].x, &queens[i].y);
        hang[queens[i].x] = 1;
    }
}
void work()
{
    for (int i = 1; i <= n; i++)
    {
        if (hang[i])
            continue;
        ans += m;
        for (int q = 1; q <= k; q++)
        {
            if (lie[queens[q].y] != i)
                ans--;
            lie[queens[q].y] = i;
            // zuoxia
            int y = queens[q].x + queens[q].y - i;
            if (y >= 1 && y <= m)
            {
                if (lie[y] != i)
                {
                    ans--;
                }
                lie[y] = i;
            }
            y = i - queens[q].x + queens[q].y;
            if (y >= 1 && y <= m)
            {
                if (lie[y] != i)
                {
                    ans--;
                }
                lie[y] = i;
            }
        }
    }
    cout << ans;
}
int main()
{
    input();
    work();
}