#include <bits/stdc++.h>
using namespace std;
string s;
int n, min_idx;
char min_first;
void main_work()
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
    if (s.length() == 0)
    {
        printf("0\n");
        return;
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
    putchar('\n');
}
int main()
{
    int nn;
    scanf("%d", &nn);
    for (int i = 0; i < nn; i++)
    {
        main_work();
    }
}