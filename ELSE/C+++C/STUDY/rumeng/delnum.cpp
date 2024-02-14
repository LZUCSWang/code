#include <bits/stdc++.h>
using namespace std;
string s;
int n, min_idx;
char min_first;
int main()
{
    cin >> s;
    int len = s.length();
    scanf("%d", &n);
    while (n--)
    {
        for (int i = 0; i < len; i++)
        {
            if (s[i] > s[i + 1])
            {
                s.erase(i, 1);
                len--;
                break;
            }
        }
    }
    int i = 0, l = 0;
    while (s[i] == '0' && l < len - 1)
    {
        i++, l++;
    }
    for (int i = l; i < s.length(); i++)
    {
        printf("%c", s[i]);
    }
}