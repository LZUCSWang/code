#include <bits/stdc++.h>
using namespace std;
#define N 100000
#define INF 2e9
#define MAX 30
int main()
{
    string s, ans;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
    {
        if (ans.find(s[i]) != string::npos)
            continue;
        while (!ans.empty() && ans.back() > s[i] && s.find(ans.back(), i) != string::npos)
            ans.pop_back();
        ans.push_back(s[i]);
    }
    cout << ans;
}
