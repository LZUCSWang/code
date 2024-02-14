#include <stdio.h>
#include <math.h>
int main()
{
    long long int m, n;
    printf("%d", (scanf("%lld %lld", &m, &n), ((n * m >= 0) ? (n / 10 - m / 10 - 1) * 45 : (n / 10 - m / 10) * 45) + ((m < 0) ? (1 + abs(m % 10)) * abs(m % 10) / 2 : (9 + m % 10) * (9 - m % 10 + 1) / 2) + ((n < 0) ? (9 + abs(n % 10)) * (9 - abs(n % 10) + 1) / 2 : (0 + n % 10) * (n % 10 + 1) / 2) - (n - m + 1) * 4));
}