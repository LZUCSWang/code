#include<bits/stdc++.h>
#include <algorithm>
using namespace std;
// #include<math.h>
#define N 10
int datas[N];
int main()
{
    int n;
    cin>>n;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        cin>>datas[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                int len = datas[i] + datas[j] + datas[k];
                int m = max(datas[i], max(datas[j], datas[k]));
                if (len - m > m)
                {
                    cnt = max(len, cnt);
                }
            }
        }
    }
    cout<<cnt<<endl;
}