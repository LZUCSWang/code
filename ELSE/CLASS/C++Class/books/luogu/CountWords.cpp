#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
int main()
{
    string datas, b;
    getline(cin, datas);
    getline(cin, b);
    for (int i = 0; i < datas.size(); i++)
        datas[i] = tolower(datas[i]);
    for (int i = 0; i < b.size(); i++)
        b[i] = tolower(b[i]);
    datas = ' ' + datas + ' ';
    b = ' ' + b + ' ';
    if (b.find(datas) != string::npos)
    {
        int start = b.find(datas), pos = b.find(datas), cnt = 0;
        while (pos != string::npos)
        {
            cnt++;
            pos = b.find(datas, pos + 1);
        }
        cout << cnt << " " << start << endl;
    }
    else
        cout << -1 << endl;
}