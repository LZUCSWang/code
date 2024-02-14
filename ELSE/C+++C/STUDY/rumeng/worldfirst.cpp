#include <bits/stdc++.h>
using namespace std;
#define MAX 10001
int t, mod;
short ans[MAX][MAX];
short dfs(int x, int y)
{
    if (ans[x][y] == -1)
    {
        printf("error\n");
        return -1;
    }
    if (ans[x][y])
    {
        printf("%d", ans[x][y]);
        return ans[x][y];
    }
    if (x == 0)
    {
        printf("1\n");
        ans[x][y] = 1;
        return 1;
    }
    else if (y == 0)
    {
        printf("2\n");
        ans[x][y] = 2;
        return 2;
    }
    ans[x][y] = -1;
    ans[x][y] = dfs((x + y) % mod, ((x + y) % mod + y) % mod);
    return ans[x][y];
}
int main()
{
    cin >> t >> mod;
    int x, y;
    while (t--)
    {
        ans[x][y] = -1;
        scanf("%d%d", &x, &y);
        ans[x][y] = dfs(x, y);
    }
}