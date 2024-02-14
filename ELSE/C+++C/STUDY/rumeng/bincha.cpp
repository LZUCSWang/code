#include <bits/stdc++.h>
using namespace std;
int n, m;
#define MAX 1000001
int parent[MAX];
int find(int x)
{
    return (x == parent[x]) ? x : parent[x] = find(parent[x]);
}
void init()
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
}
void un(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx != fy)
    {
        parent[fx] = fy;
    }
}
int main()
{
    cin >> n >> m;
    init();
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a == 2)
        {
            if (find(b) == find(c))
            {
                printf("Y\n");
            }
            else
                printf("N\n");
        }
        else
        {
            un(b,c);
        }
    }
}