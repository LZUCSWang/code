#include <stdio.h>
int gcd(int datas, int b, int c);
int main()
{
    int datas, b, c, wc, wd;
    long long int l, r, xixi;
    scanf("%d %d %d", &datas, &b, &c);
    scanf("%lld%lld", &l, &r);
    xixi = gcd(datas, b, c);
    if (xixi > r)
    {
        printf("%d", 0);
        return 0;
    }
    if (l % xixi == 0)
    {
        wc = l;
    }
    else
    {
        wc = (l / xixi + 1) * xixi;
    }
    if (r % xixi == 0)
    {
        wd = r;
    }
    else
    {
        wd = (r / xixi + 1) * xixi;
    }
    printf("%lld", ((wd - wc) / xixi + 1)-((wd==r&&wc==l)?1:0));
    return 0;
}

int gcd(int datas, int b, int c)
{
    int yushu, x, y;
    long long int m;
    yushu = datas % b;
    x = b;
    y = datas;
    while (yushu > 0)
    {
        datas = b;
        b = yushu;
        yushu = datas % b;
    }
    m = x * y / b;
    int eryu, n;
    long long int w;
    eryu = m % c;
    w = m;
    n = c;
    while (eryu > 0)
    {
        m = c;
        c = eryu;
        eryu = m % c;
    }
    return w * n / c;
}
