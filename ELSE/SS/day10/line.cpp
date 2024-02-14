#include <bits/stdc++.h>
using namespace std;
map<string, int> datas;
char str[20];
int n, m, nn, val;
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d", str, &val);
        if (val < m)
            val = m;
        datas[str] += val;
    }
    scanf("%d", &nn);
    for (int i = 0; i < nn; i++)
    {
        scanf("%s", str);
        if (datas.find(str) == datas.end())
        {
            printf("No Info\n");
        }
        else
        {
            printf("%d\n", datas[str]);
        }
    }
}