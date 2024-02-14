// 5
// 1 2
// 2 3
// 3 4
// 4 5
// 1 5 2 3 10

#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000

int head[MAX], idx;
struct Node
{
    int to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = Node{v, head[u]};
    head[u] = idx;
}

int n, mod = 10007;
int max_ans, sum_ans;
int v[MAX];
void work(int now)
{
    int sum = 0, max_temp = 0;
    for (int i = head[now]; i; i = edge[i].nex)
    {
        int to = edge[i].to;
        max_ans = max(max_ans, v[to] * max_temp);
        sum_ans = (sum_ans + sum * v[to]) % mod;
        max_temp = max(max_temp, v[to]);
        sum = (sum + v[to]) % mod;
    }
}

void input()
{
    cin >> n;
    for (int i = 1, a, b; i <= n - 1; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", v + i);
}

int main()
{
    input();
    for (int i = 1; i <= n; i++)
        work(i);
    cout << max_ans << ' ' << sum_ans * 2%mod;
}