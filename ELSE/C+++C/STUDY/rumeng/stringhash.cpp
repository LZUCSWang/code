#include <bits/stdc++.h>
using namespace std;
set<string> s;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string temp;
        cin >> temp;
        s.insert(temp);
    }
    printf("%d", s.size());
}