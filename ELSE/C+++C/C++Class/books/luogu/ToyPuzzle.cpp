#include <bits/stdc++.h>
using namespace std;
int n, m;
int main()
{
    cin >> n >> m;
    string toy[n];
    int flag1[n], step, index = 0, flag2;
    for (int i = 0; i < n; i++)
        cin >> flag1[i] >> toy[i];
    for (int i = 0; i < m; i++)
    {
        cin >> flag2 >> step;
        if (flag2 == 0 && flag1[index] == 0 || flag2 == 1 && flag1[index] == 1)
            index = (index + n - step) % n;
        else
            index = (index + step) % n;
    }
    cout << toy[index] << endl;
}