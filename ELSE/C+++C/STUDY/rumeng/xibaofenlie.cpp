#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2147483647
#define MAX 30010
int n, m1, m2, now, all_su, su[MAX];
int m_prime[MAX], c_prime[MAX];
bool su_shai[MAX];
void sushushai()
{
    for (int i = 2; i <= MAX; i++)
    {
        if (!su_shai[i])
            su[++all_su] = i;
        for (int j = 1; j <= all_su && i * su[j] <= MAX; j++)
        {
            su_shai[i * su[j]] = true;
            if (i % su[j] == 0)
                break;
        }
    }
}
int main()
{
    cin >> n >> m1 >> m2;
    sushushai();
    int ii = 1;
    while (m1 != 1)
    {
        while (m1 % su[ii] == 0)
        {
            m_prime[ii] += m2;
            m1 /= su[ii];
        }
        ii++;
    }
    bool flag, flag_ans = false;
    int min_ans = INF;
    for (int i = 1; i <= n; i++)
    {
        int ans = 0;
        flag = false;
        scanf("%d", &now);
        memset(c_prime, 0, sizeof(c_prime));
        for (int j = 1; j <= all_su; j++)
        {
            while (now % su[j] == 0)
            {
                c_prime[j]++;
                now /= su[j];
            }
        }
        for (int j = 1; j <= all_su; j++)
        {
            if (!c_prime[j] && m_prime[j])
            {
                flag = true;
                break;
            }
            if (c_prime[j] && m_prime[j])
            {
                int t = m_prime[j] / c_prime[j];
                if (m_prime[j] % c_prime[j] == 0)
                    ans = max(ans, t);
                else
                    ans = max(ans, t + 1);
            }
        }
        if (!flag)
        {
            min_ans = min(min_ans, ans);
            flag_ans = true;
        }
    }
    if (flag_ans)
        printf("%d", min_ans);
    else
        printf("-1");
}