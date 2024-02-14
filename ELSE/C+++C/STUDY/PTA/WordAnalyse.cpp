#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
typedef long long ll;
int a[30];
ll n;
int ans;
char anschar;
int main()
{
    string s;
    ios::sync_with_stdio(false);
    cin >> s;
    ans = -1;
    for (int i = 0; i < s.length(); i++)
    {
        a[s[i] - 'a']++;
        for (int j = 25; j >= 0; j--)
        {
            if (a[j] >= ans)
            {
                ans = a[j];
                anschar = j + 'a';
            }
        }
    }
    cout << anschar << endl
         << ans << endl;
}