#include <stdio.h>
int count(int x, int t)
{
    int cnt = 0;
    while (x)
    {
        if (x % 10 == t)
            cnt++;
        x /= 10;
    }
    return cnt;
}
int main()
{
    int n, cnt = 0, t;
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= n; i++)
    {
        cnt += count(i, t);
    }
    printf("%d", cnt);
}