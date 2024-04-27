#include <bits/stdc++.h>
using namespace std;
#define MAX 2005

char ch[MAX];
int n, ans;
bitset<MAX> bit_sets[MAX];
void input()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        getchar();
        scanf("%s", ch + 1);
        for (int j = 1; j <= n; ++j)
            if (ch[j] == '1')
                bit_sets[i][j] = 1;
        bit_sets[i][i] = 1;
    }
}
void cnt()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            if (bit_sets[j][i])
                bit_sets[j] |= bit_sets[i];
        }
    for (int i = 1; i <= n; ++i)
        ans += bit_sets[i].count();
}
int main()
{
    input();
    cnt();
    printf("%d", ans);
    return 0;
}