#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
int main()
{
    int data[10];
    for (int i = 0; i < 10; i++)
    {
        cin >> data[i];
    }
    int high;
    cin >> high;
    int cnt = 0;
    for (int i = 0; i < 10; i++)
    {
        if (data[i] <= high + 30)
            cnt++;
    }
    cout << cnt << endl;
}