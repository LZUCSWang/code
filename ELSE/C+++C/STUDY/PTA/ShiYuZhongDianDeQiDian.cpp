#include <bits/stdc++.h>
using namespace std;
#define MAXN 10000000
typedef long long ll;
int a[MAXN];
int M;
int main()
{
    ios::sync_with_stdio(false);
    cin >> M;
    a[0] = 0;
    a[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        a[i] = (a[i - 1] + a[i - 2]) % M;
        if (a[i] == 1 && a[i - 1] == 0)
        {
            cout << i - 1 << endl;
            break;
        }
    }
}