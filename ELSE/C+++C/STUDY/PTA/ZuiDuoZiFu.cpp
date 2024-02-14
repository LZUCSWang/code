#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
typedef long long ll;
int a[MAXN];
ll n;
int main()
{
    ios::sync_with_stdio(false);
    int ans = 0;
    char b;
    while (true)
    {
        cin >> b;
        if (b == '#')
            break;
        // if (b != '\n')
        a[b - 'A' + 1]++;
    }
    printf("%d", max(a[1], max(a[2], max(a[3], max(a[4], max(a[5], max(a[6], max(a[7], max(a[8], max(a[9], max(a[10], max(a[11], max(a[12], max(a[13], max(a[14], max(a[15], max(a[16], max(a[17], max(a[18], max(a[19], max(a[20], max(a[21], max(a[22], max(a[23], max(a[24], max(a[25], max(a[26], 0)))))))))))))))))))))))))));
}