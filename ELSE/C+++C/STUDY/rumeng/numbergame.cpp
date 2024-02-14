#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
ll a, b, c, x;
bool work()
{
    scanf("%lld%lld%lld%lld", &a, &b, &c, &x);
    if (x == c)
    {
        return true;
    }
    ll b1 = b, b2 = a - b;
    if (b1 == b2)
    {
        if (b - c == x)
            return true;
    }
    ll t1 = b1 - c;
    if (t1 == x)
    {
        return true;
    }
    if ((x - t1) * (b1 - b2) > 0)
    {
        if ((x - t1) % (b1 - b2) == 0)
        {
            return true;
        }
    }
    swap(b1, b2);
    t1 = b1 - c;
    if (t1 == x)
    {
        return true;
    }
    if ((x - t1) * (b1 - b2) > 0)
    {
        if ((x - t1) % (b1 - b2) == 0)
        {
            return true;
        }
    }
    swap(b1, b2);
    ll t2 = b2 - b1 + c;
    if (t2 == x)
    {
        return true;
    }
    if ((x - t2) * (b2 - b1) > 0)
    {
        if ((x - t2) % (b2 - b1) == 0)
        {
            return true;
        }
    }
    swap(b1, b2);
    t2 = b2 - b1 + c;
    if (t2 == x)
    {
        return true;
    }
    if ((x - t2) * (b2 - b1) > 0)
    {
        if ((x - t2) % (b2 - b1) == 0)
        {
            return true;
        }
    }
    return false;
}
ll t;
int main()
{
    scanf("%lld", &t);
    while (t--)
        if (work())
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
}