#include <bits/stdc++.h>
using namespace std;
string str;
int maxcount, j;
void deal()
{
    int len = str.length();
    for (int i = 0; i < len; i++)
    {
        int cnt = 1;
        for (int k = i + 1; k < len - j + 1; k++)
        {
            if ((str.substr(i, j) == str.substr(k, j)))
                cnt++;
        }
        maxcount = max(maxcount, cnt);
    }
}
int main()
{
    cin >> str;
    cin >> j;
    if (j==1){
        for (int i=0;i<str.length();i++){
        }

    }
    deal();
    cout << maxcount;
}