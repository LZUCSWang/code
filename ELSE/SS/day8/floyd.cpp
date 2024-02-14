#include <bits/stdc++.h>
#define MAX_N 105
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long int
ll datas[MAX_N][MAX_N];
ll n, m;
ll parent[MAX_N][MAX_N];
void print()
{
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            if (datas[i][j] == INF)
            {
                printf("%3d ", -1);
            }
            else
            {
                printf("%3d ", datas[i][j]);
            }
        }
        printf("\n");
    }
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            printf("%3d ", parent[i][j]);
        }
        printf("\n");
    }
}
void print_path(ll start, ll end)
{
    ll k = parent[start][end];
    printf("%lld->", start);
    while (k != end)
    {
        printf("%lld->", k);
        k = parent[k][end];
    }
    printf("%lld:", end);
}
void init_flord()
{
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            if (i == j)
            {
                datas[i][j] = 0;
            }
            else
            {
                datas[i][j] = INF;
            }
            parent[i][j] = j;
        }
    }
}
int main()
{
    cin >> n >> m;
    init_flord();
    for (ll i = 1; i <= m; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        datas[a][b] = c;
    }
    for (ll k = 0; k < n; k++)
    {
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < n; j++)
            {
                if (datas[i][k] + datas[k][j] < datas[i][j])
                {

                    parent[i][j] = parent[i][k];
                    datas[i][j] = datas[i][k] + datas[k][j];
                }
            }
        }
    }
    // print();
    ll s, e;
    for (ll i = 1; i <= 2; i++)
    {
        cin >> s >> e;
        print_path(s, e);
        if (datas[s][e] != INF)
        {
            printf("%lld\n", datas[s][e]);
        }
        else
        {
            printf("-1\n");
        }
    }
    ll max_i = 0, max_j = 0, max_dis = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            if (datas[i][j] != INF && datas[i][j] > max_dis)
            {
                max_dis = datas[i][j];
                max_i = i;
                max_j = j;
            }
            if (datas[i][j] != INF && datas[i][j] == max_dis && i < max_i)
            {
                max_i = i;
                max_j = j;
            }
        }
    }
    print_path(max_i, max_j);
    printf("%lld", max_dis);
    // print();
}