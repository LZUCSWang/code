#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
// #define MAX 100000
bool cmp(string datas, string b)
{
    return datas + b > b + datas;
}
int main()
{
    int n;
    cin >> n;
    string s[n];
    for (int i = 0; i < n; i++)
        cin >> s[i];

    sort(s, s + n, cmp);
    for (int i = 0; i < n; i++)
        cout << s[i];
}