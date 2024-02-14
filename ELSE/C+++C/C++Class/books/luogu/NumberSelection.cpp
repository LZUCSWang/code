#include <bits/stdc++.h>
using namespace std;
#define MAX 100000
int n, m;
int datas[MAX], cnt = 0;
int judge(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;
    return 1;
}
void dfs(int *visit, int sum, int now, int left)
{
    if (left == 0)
    {
        if (judge(sum))
            cnt++;
        return;
    }
    for (int i = now; i <= n; i++)
        dfs(visit, sum + datas[i], i + 1, left - 1);
}
int main()
{
    int visit[MAX] = {0};
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> datas[i];
    dfs(visit, 0, 1, m);
    cout << cnt << endl;
}