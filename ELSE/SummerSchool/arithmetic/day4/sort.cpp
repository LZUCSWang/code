#include <bits/stdc++.h>
using namespace std;
#define MAX 100000001
int datas[MAX];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &datas[i]);
    }
    sort(datas, datas + n);
    for (int i = 0; i < n; i++)
    {
        printf("%d", datas[i]);
        if (i != n - 1)
        {
            printf(" ");
        }
    }
}