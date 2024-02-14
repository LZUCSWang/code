#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
string s;
char temp[MAX];
int ans, k;
int main()
{
    while (getline(cin, s))
    {
        ans = 0;
        bool have_num = false;
        for (int i = 0; i < s.length(); i++)
        {
            if (i && isdigit(s[i - 1]) && !isdigit(s[i]))
                continue;
            if (s[i] == '-' && i < s.length() - 1 && isdigit(s[i + 1]))
            {
                k = 0;
                have_num = true;
                temp[k++] = s[i];
                i++;
                while (i < s.length() && isdigit(s[i]))
                {
                    temp[k++] = s[i];
                    i++;
                }
                temp[k] = 0;
                ans += atoi(temp);
                continue;
            }
            if (isdigit(s[i]))
            {
                k = 0;
                have_num = true;
                temp[k++] = s[i];
                i++;
                while (i < s.length() && isdigit(s[i]))
                {
                    temp[k++] = s[i];
                    i++;
                }
                temp[k] = 0;
                ans += atoi(temp);
                continue;
            }
        }
        if (have_num)
        {
            cout << ans << endl;
        }
    }
}