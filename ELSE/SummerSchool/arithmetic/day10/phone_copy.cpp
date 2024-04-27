#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int Z = 10;
int nn, n, tot, ch[N][Z];
bool bo[N];
char s[20];
int len, u;
bool flag, ans;

int main()
{
    scanf("%d", &nn);
    while (nn--)
    {
        scanf("%d", &n);
        tot = 1;
        memset(ch, 0, sizeof(ch));
        memset(bo, false, sizeof(bo));
        ans = false;
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s);
            len = strlen(s);
            u = 1;
            flag = false;
            for (int ii = 0; ii < len; ii++)
            {
                int c = s[ii] - '0';
                if (!ch[u][c])
                    ch[u][c] = ++tot;
                else if (ii == len - 1)
                    flag = true;
                u = ch[u][c];
                if (bo[u])
                    flag = true;
            }
            bo[u] = true;
            if (flag)
                ans = true;
        }
        if (!ans)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
