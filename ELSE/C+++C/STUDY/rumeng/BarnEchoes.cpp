#include <bits/stdc++.h>
using namespace std;
#define MAX 100001
string a, b;
int main()
{
    cin >> a;
    cin >> b;
    if (a.length() < b.length())
    {
        swap(a, b);
    }
    for (int lenth = b.length(); lenth >= 0; lenth--)
    {
        string prea = a.substr(0, lenth), suba = a.substr(a.length() - lenth, lenth);
        string preb = b.substr(0, lenth), subb = b.substr(b.length() - lenth, lenth);
        if (prea == subb || suba == preb)
        {
            printf("%d", lenth);
            return 0;
        }
    }
}