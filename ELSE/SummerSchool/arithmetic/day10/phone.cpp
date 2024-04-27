#include <bits/stdc++.h>
using namespace std;
#define N 10005
#define Z 11
int n, nn, all_num, tries[N][Z], len, u;
bool flags[N], ans, flag;
char s[30];
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &nn);
        all_num = 1, ans = false;
        for (int ii = 0; ii < nn; ii++)
        {
            scanf("%s", s);
            flag = false, len = strlen(s), u = 1;
            for (int i = 0; i < len; i++)
            {
                int c = s[i] - '0';
                if (!tries[u][c])
                {
                    tries[u][c] = ++all_num;
                    u = tries[u][c];
                    if (flags[u])
                        flag = true;
                }
                else if (i == len - 1)
                {
                    flag = true;
                    u = tries[u][c];
                    if (flags[u])
                        flag = true;
                }
                else
                {
                    u = tries[u][c];
                    if (flags[u])
                        flag = true;
                }
            }
            flags[u] = true;
            if (!ans && flag)
                ans = true;
        }
        if (!ans)
        {
            printf("YES\n");
            memset(tries, 0, sizeof(tries));
            memset(flags, false, sizeof(flags));
            continue;
        }
        memset(tries, 0, sizeof(tries));
        memset(flags, false, sizeof(flags));
        printf("NO\n");
    }
    return 0;
}
