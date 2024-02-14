#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long int
bitset<maxn> datas[maxn];
ll n, ans = 0, i, j;
int main()
{
    char t;
    string s;
    scanf("%lld", &n);
    if (n == 1)
    {
        printf("1\n");
        return 0;
    }
    for (i = 0; i < n; i++)
    {
        cin >> s;
        for (j = 0; j < n; j++)
        {
            if (s[j] == '1')
                datas[i][j] = 1;
        }
        datas[i][i] = 1;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (datas[j][i])
                datas[j] |= datas[i];
        }
    }
    for (i = 0; i < n; i++)
        ans += datas[i].count();
    printf("%lld\n", ans);
    return 0;
}