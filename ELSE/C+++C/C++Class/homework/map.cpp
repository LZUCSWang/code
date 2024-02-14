#include <bits/stdc++.h>
#include <string.h>
using namespace std;
int main()
{
    map<string, string> mp;
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        string a, b;
        cin >> a >> b;
        mp[a] = b;
    }
    for (int i = 0; i < n; i++)
    {
        string a;
        cin >> a;
        if (mp[a].size() == 0)
        {
            cout << "ou" << endl;
        }
        else
        {
            cout << mp[a] << endl;
        }
    }
}