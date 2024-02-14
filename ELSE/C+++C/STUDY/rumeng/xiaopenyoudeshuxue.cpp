#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000005
#define ll long long
const ll MaxN = 1e6;
const ll Base = (ll)1e9;
struct pii
{
    ll high, low;
    friend inline pii operator+(const pii &a, const pii &b)
    {
        pii c;
        c.high = a.high + b.high;
        c.low = a.low + b.low;
        if (c.high >= 0 && c.low >= Base)
        {
            c.high += c.low / Base;
            c.low = c.low % Base;
        }
        if (c.high <= 0 && c.low <= -Base)
        {
            c.high += c.low / Base;
            c.low = c.low % Base;
        }
        if (c.high > 0 && c.low < 0)
        {
            c.high--;
            c.low += Base;
        }
        if (c.high < 0 && c.low >= Base)
        {
            c.high++;
            c.low -= Base;
        }
        return c;
    }
    friend inline bool operator<(const pii &a, const pii &b)
    {
        if (a.high == b.high)
            return a.low < b.low;
        else
            return a.high < b.high;
    }
    friend inline pii max(const pii &a, const pii &b)
    {
        if (a < b)
            return b;
        else
            return a;
    }
} anss[MAX], dpp[MAX], nums[MAX], lasts[MAX], ans;
ll n, p;
int main()
{
    scanf("%lld%lld", &n, &p);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &nums[i].low);
    ans = anss[1] = dpp[1] = lasts[1] = nums[1];
    for (int i = 2; i <= n; i++)
    {
        lasts[i] = max(nums[i], nums[i] + lasts[i - 1]);
        dpp[i] = max(dpp[i - 1], lasts[i]);
        anss[i] = (i == 2) ? nums[1] + nums[1] : max(anss[i - 1], dpp[i - 1] + anss[i - 1]);
        ans = max(ans, anss[i]);
    }
    cout << (((ans.high % p) * Base) % p + ans.low % p)%p << endl;
}
