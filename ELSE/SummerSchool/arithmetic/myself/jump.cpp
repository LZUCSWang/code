#include <bits/stdc++.h>
using namespace std;
#define MAX 10001
int datas[MAX];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> datas[i];
    sort(datas + 1, datas + n + 1);
    long long int cnt = pow(datas[n], 2);
    int left = 1, right = n;
    int flag = 1;
    while (left < right)
    {
        cnt += pow(datas[right] - datas[left], 2);
        if (flag == 1)
            right--;
        else
            left++;
        flag *= -1;
    }
    cout << cnt;
}