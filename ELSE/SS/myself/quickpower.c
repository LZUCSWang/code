#include <stdio.h>
int main()
{
    long long int datas, b, c;
    scanf("%lld %lld %lld", &datas, &b, &c);
    long long int cnt = 1, base = datas, bb = b;
    while (b)
    {
        if (b & 1)
        {
            cnt *= base;
            // cnt %= c;
        }
        base *= base;
        // base %= c;
        b >>= 1;
    }
    printf("%ld^%ld mod %ld=%ld", datas, bb, c, cnt);
}