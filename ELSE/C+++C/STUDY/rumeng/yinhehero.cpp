#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int n, ii, jj, parent[MAX], cnt, front[MAX], nums[MAX], fx, fy;
char flag;
int fa(int x)
{
    if (x == parent[x])
        return x;
    int ffx = fa(parent[x]);
    front[x] += front[parent[x]];
    parent[x] = ffx;
    return ffx;
}
void M()
{
    front[fx] += nums[fy];
    parent[fx] = fy;
    nums[fy] += nums[fx];
    nums[fx] = 0;
}
void C()
{
    if (fx != fy)
        printf("-1\n");
    else
        printf("%d\n", abs(front[ii] - front[jj]) - 1);
}
void init()
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
        front[i] = 0;
        nums[i] = 1;
    }
}
int main()
{
    cin >> n;
    init();
    for (int i = 1; i <= n; i++)
    {
        cin >> flag >> ii >> jj;
        fx = fa(ii), fy = fa(jj);
        if (flag == 'M')
            M();
        else
            C();
    }
}