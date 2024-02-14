#include <bits/stdc++.h>
using namespace std;
#define ll long long
// 4 5
// 24 15 61 88
int n, m;
int hashs[1000005];
int flag[1000005];
int main()
{
    cin >> n >> m;
    memset(flag, -1, sizeof(flag));
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if (flag[a] != -1)
        {
            printf("%d", flag[a]);
            if (i != n - 1)
                printf(" ");
            continue;
        }
        int t = a;
        a = a % m;
        while (hashs[a] != 0)
        {
            a = (a + 1) % m;
        }
        hashs[a] = 1;
        flag[t] = a;
        printf("%d", a);
        if (i != n - 1)
        {
            printf(" ");
        }
    }
}