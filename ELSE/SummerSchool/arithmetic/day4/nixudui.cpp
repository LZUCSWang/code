#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
long long int datas[MAX];
int main()
{
    long long int cnt = 0;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &datas[i]);
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (datas[i] > datas[j])
            {
                cnt++;
            }
        }
    }
    printf("%lld", cnt);
}