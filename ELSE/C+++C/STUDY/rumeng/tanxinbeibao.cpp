#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
ll n, t;
ll datas[MAX];
struct node
{
    ll cun;
    double dan;
} nodes[MAX];
bool cmp(node a, node b)
{
    return a.dan > b.dan;
}
void input()
{
    scanf("%lld%lld", &n, &t);
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        nodes[i].cun = a;
        nodes[i].dan = b * 1.0 / a;
    }
    sort(nodes + 1, nodes + 1 + n, cmp);
}

double ans;
void work()
{
    for (int i = 1; i <= n; i++)
    {

        if (nodes[i].cun <= t)
        {
            ans += nodes[i].cun * nodes[i].dan;
        }
        else
        {
            ans += nodes[i].dan * t;
            break;
        }
        t -= nodes[i].cun;
    }
    printf("%.2lf", ans);
}
int main()
{
    input();
    work();
}