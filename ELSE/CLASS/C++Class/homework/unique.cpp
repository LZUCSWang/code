#include <bits/stdc++.h>
using namespace std;
int n;
map<int, bool> mp;
int main()
{
    scanf("%d", &n);
    int t;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &t);
        if (mp[t] == false)
        {
            mp[t] = true;
            printf("%d ", t);
        }
    }
}
