#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 7000005
#define ll long long

// 3 7 1 1 3 1
// 3 3 2

int n, m, q, u, v, t;
int a[MAX];
int top_a, h, h1, h2, t1, t2, toadd;
int cut1[MAX], cut2[MAX], now;
double p;
void input()
{
    cin >> n >> m >> q >> u >> v >> t;
    for (top_a = 1; top_a <= n; top_a++)
        scanf("%d", a + top_a);
}
bool cmp(int a, int b)
{
    return a > b;
}
priority_queue<int> qq;
int main()
{
    input();
    top_a--;
    sort(a + 1, a + top_a + 1, cmp);
    p = double(u) / double(v);
    h = h1 = h2 = 1;
    for (int i = 1, a1, a2; i <= m; i++)
    {
        if (h > top_a)
            if (cut1[h1] > cut2[h2])
                now = cut1[h1++];
            else
                now = cut2[h2++]; // find in cut1 and 2;
        else if (a[h] >= cut1[h1] && a[h] >= cut2[h2])
            now = a[h++]; // in a
        else if (cut1[h1] >= a[h] && cut1[h1] >= cut2[h2])
            now = cut1[h1++]; // in cut1
        else
            now = cut2[h2++]; // in cut 2
        now += toadd;
        toadd += q;
        a1 = floor(p * double(now)), a2 = now - a1;
        a1 -= toadd;
        a2 -= toadd;
        cut1[++t1] = a1;
        cut2[++t2] = a2;
        if (i % t == 0)
            printf("%d ", now);
    }
    printf("\n");
    for (int i = h; h <= top_a; h++)
        qq.push(a[h]);
    for (int i = h1; i <= t1; i++)
        qq.push(cut1[i]);
    for (int i = h2; i <= t2; i++)
        qq.push(cut2[i]);
    for (int i = 1; !qq.empty(); i++)
    {
        if (i % t == 0)
            printf("%d ", qq.top() + toadd);
        qq.pop();
    }
}