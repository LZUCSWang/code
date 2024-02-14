#include <bits/stdc++.h>
using namespace std;
#define MAX 1000
int main()
{
    int data[MAX];
    int n, m;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &data[i]);
        }
        sort(data + 1, data + n + 1);
        for (int i = 1; i <= n; i++)
        {
            printf("%d", data[i]);
            if (i != n)
            {
                printf(" ");
            }
        }
        printf("\n");
        scanf("%d", &m);
        for (int i = 1; i <= m; i++)
        {
            int target;
            scanf("%d", &target);
            int flag = 0;
            for (int j = 1; j <= n; j++)
                if (data[j] == target)
                {
                    flag = 1;
                    break;
                }
            if (flag == 0)
                printf("0");
            else
                printf("%d", lower_bound(data + 1, data + n + 1, target) - data);
            if (i != m)
                printf(" ");
        }
    }
}