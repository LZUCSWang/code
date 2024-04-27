#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#define MAX 100000
int main()
{
    char t;
    int cnt = 0;
    while (true)
    {
        t = getchar();
        if (t == '\n')
        {
            cout << cnt << endl;
            // break;
            return 0;
        }
        if (t == ' ')
            continue;
        cnt++;
    }
}