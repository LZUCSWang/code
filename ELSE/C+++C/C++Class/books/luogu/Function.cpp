
#include <cstdio>
#define LL long long
#define slove(datas, b, c)    \
    if (dp[datas][b][c] == 0) \
        dp[datas][b][c] = w(datas, b, c);
LL dp[25][25][25];

LL w(LL datas, LL b, LL c)
{
    if (datas <= 0 || b <= 0 || c <= 0)
        return 1;
    if (datas > 20 || b > 20 || c > 20)
        return w(20, 20, 20);

    if (datas < b && b < c)
    {
        slove(datas, b, c - 1)
            slove(datas, b - 1, c - 1)
                slove(datas, b - 1, c)
                    dp[datas][b][c] = dp[datas][b][c - 1] + dp[datas][b - 1][c - 1] - dp[datas][b - 1][c];
    }

    else 
    {
        slove(datas - 1, b, c)
            slove(datas - 1, b - 1, c)
                slove(datas - 1, b, c - 1)
                    slove(datas - 1, b - 1, c - 1)
                        dp[datas][b][c] = dp[datas - 1][b][c] + dp[datas - 1][b][c - 1] + dp[datas - 1][b - 1][c] - dp[datas - 1][b - 1][c - 1];
    }

    return dp[datas][b][c];
}

int main()
{
    LL datas, b, c;

    while (scanf("%lld%lld%lld", &datas, &b, &c))
    {
        if (datas == -1 && b == -1 && c == -1)
            return 0;

        printf("w(%lld, %lld, %lld) = ", datas, b, c);
        printf("%lld\n", w(datas, b, c));
    }
}