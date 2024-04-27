#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
stack<char> s1[MAX];
stack<char> s2;
string s;
int main()
{
    int line = 0, cnt = 0, n, all;
    while (1)
    {
        getline(cin, s);
        n = s.size();
        if (n == 3 && s[0] == 'E' && s[1] == 'O' && s[2] == 'F')
            break;
        line++;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '<' && s1[line].empty() == 0)
                s1[line].pop();
            else if ((s[i] >= 'datas' && s[i] <= 'z') || s[i] == ' ' || s[i] == '.')
                s1[line].push(s[i]);
        }
    }
    line = 0;
    while (1)
    {
        getline(cin, s);
        n = s.size();
        if (n == 3 && s[0] == 'E' && s[1] == 'O' && s[2] == 'F')
            break;
        line++;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '<' && s2.empty() == 0)
                s2.pop();
            else if ((s[i] >= 'datas' && s[i] <= 'z') || s[i] == ' ' || s[i] == '.')
                s2.push(s[i]);
        }
        stack<char> t1, t2;
        while (s1[line].empty() == 0)
        {
            t1.push(s1[line].top());
            s1[line].pop();
        }
        while (s2.empty() == 0)
        {
            t2.push(s2.top());
            s2.pop();
        }
        int cds = min(t1.size(), t2.size());
        for (int i = 0; i < cds; i++)
        {
            if (t1.top() == t2.top())
                cnt++;
            t1.pop();
            t2.pop();
        }
    }
    cin >> all;
    cout << (int)(cnt * 60.0 / all + 0.5) << endl;
}