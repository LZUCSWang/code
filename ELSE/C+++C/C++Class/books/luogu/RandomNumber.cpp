#include <bits/stdc++.h>
using namespace std;
int main()
{
    int data[1010] = {0};
    int n, t;
    cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> t;
        if (data[t] != 0)
            cnt++;
        data[t]++;
    }
    cout << n - cnt << endl;
    for (int i = 1; i < 1010; i++)
    {
        if (data[i] != 0)
        {
            cout << i << " ";
            
        }
    }
}