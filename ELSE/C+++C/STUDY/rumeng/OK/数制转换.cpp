#include <bits/stdc++.h>
using namespace std;
int r;
void opera(int n)
{
    if (n == 0)
        return;
    int m = n % r;
    if (m < 0)
    {
        m -= r;
        n += r;
    }
    if (m < 10)
    {
        m += '0';
    }
    else
    {
        m += 'A' - 10;
    }
    opera(n / r);
    printf("%c", m);
}
int main()
{
    int n;
    cin >> n >> r;
    printf("%d=", n);
    opera(n);
    printf("(base%d)", r);
}