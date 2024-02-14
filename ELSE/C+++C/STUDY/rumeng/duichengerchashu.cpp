#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000020
#define ll long long
struct node
{
    ll val, left, right;
} Nodes[MAX];
int n;
void input()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &Nodes[i].val);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &Nodes[i].left, &Nodes[i].right);
    }
}
bool judge(int nowl,int nowr)
{
    if (nowl == -1 && nowr == -1)
        return true;
    if (nowl == -1 || nowr == -1)
        return false;
    if (Nodes[nowl].val != Nodes[nowr].val)
        return false; 
    return judge(Nodes[nowl].left,Nodes[nowr].right) && judge(Nodes[nowl].right,Nodes[nowr].left);
}
ll ans = 1;
ll count(int now)
{
    return now == -1 ? 0 : count(Nodes[now].left) + count(Nodes[now].right) + 1;
}
int main()
{
    input();
    for (int i = 1; i <= n; i++)
    {
        if (judge(i,i))
            ans = max(ans, count(i));
    }
    printf("%lld", ans);
}