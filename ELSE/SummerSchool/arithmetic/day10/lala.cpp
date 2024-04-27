#include<bits/stdc++.h>
#define dbg(x) cout << #x << " = " << x << endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1002000;
const int mod = 19930726;
char str[maxn], str1[maxn * 2];
int p[maxn * 2], b[maxn];
LL Pow(LL a, LL b);
int Insert(char str[]);

int main()
{
    int n, len, mx, id, i, j;
    LL k, sum;
    scanf("%d %lld %s", &n, &k, str);
    len = Insert(str);
    mx = 0;
    for (i = 1; i < len; i++)
    {
        p[i] = mx > i ? min(mx - i, p[2 * id - i]) : 1;
        while (str1[i - p[i]] == str1[i + p[i]])
            p[i]++;
        if (i + p[i] > mx)
        {
            mx = i + p[i];
            id = i;
        }
        if (isalpha(str1[i]))
        {
            sum += (p[i]) / 2;
            b[p[i] - 1]++;
        }
    }
    if (k > sum)
        printf("-1\n");
    else
    {
        LL ans = 1;
        for (i = n; i >= 1; i--)
        {

            b[i] += b[i + 1];
            if (i % 2 == 0)
                continue;
            if (k > b[i])
            {
                ans = ans * Pow(i, b[i]) % mod;
                k -= b[i];
            }
            else
            {
                ans = ans * Pow(i, k) % mod;
                break;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}

int Insert(char str[])
{
    int i, j = 2;
    str1[0] = '!';
    str1[1] = '#';
    for (i = 0; str[i]; i++)
    {
        str1[j] = str[i];
        str1[j + 1] = '#';
        j += 2;
    }
    str1[j] = 0;
    return j;
}

LL Pow(LL a, LL b)
{
    LL n = 1;
    while (b)
    {
        if (b & 1)
            n = n * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return n;
}