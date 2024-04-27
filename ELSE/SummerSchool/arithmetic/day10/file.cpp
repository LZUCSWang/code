#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define N 2000005
#define Mod 19930726
char st[N], s[N];
int p[N], cnt[N], n, k;
int change()
{
    int len = strlen(st);
    int j = 2;
    s[0] = '^';
    s[1] = '$';
    for (int i = 0; i < len; i++)
    {
        s[j++] = st[i];
        s[j++] = '$';
    }
    s[j] = '&';
    return j;
}
int Manacher()
{
    int len = change(), mid = 1, mx = 1, ans = -1;
    for (int i = 1; i < len; i++)
    {
        if (i < mx)
            p[i] = min(mx - i, p[mid * 2 - i]);
        else
            p[i] = 1;
        while (s[i - p[i]] == s[i + p[i]])
            p[i]++;
        if (mx < i + p[i])
        {
            mid = i;
            mx = i + p[i];
        }
        if ((p[i] - 1) % 2)
            cnt[p[i] - 1]++;
    }
    return ans;
}
int q_pow(int a, int b)
{
    int sum;
    for (sum = 1; b; b >>= 1, a = a * a % Mod)
        if (b & 1)
            sum = (sum * a) % Mod;
    return sum;
}
signed main()
{
    cin >> n >> k;
    scanf("%s", st);
    Manacher();
    int ans = 1, sum = 0;
    for (int i = n; i >= 1; i--)
    {
        if (!(i % 2))
            continue;
        sum += cnt[i];
        if (k >= sum)
        {
            ans = (ans * q_pow(i, sum)) % Mod;
            k -= sum;
        }
        else
        {
            ans = (ans * q_pow(i, k)) % Mod;
            k -= sum;
            break;
        }
    }
    if (k > 0)
        printf("-1");
    else
        cout << ans;
    return 0;
}