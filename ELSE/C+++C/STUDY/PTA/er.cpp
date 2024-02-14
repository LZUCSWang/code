#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
// int a[MAXN];
int n;
string s;
int main()
{
    cin >> s;
    double fu = 1.0;
    double ans = 0;
    if (s[0] == '-')
    {
        fu = 1.5;
        s = s.substr(1);
    }

    int er = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '2')
        {
            er++;
        }
        if (i == s.length() - 1 && (s[s.length() - 1] - '2') % 2 == 0)
        {
            fu *= 2;
        }
    }
    printf("%.2lf%%", 1.0 * er / s.length() * 100 * fu);
}