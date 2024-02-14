#include <stdio.h>
#define maxsize 1000000
long long int datas[maxsize];
int main()
{
    long long int n, m;
    int i, j, x, flag;
    int low, high, mid;
    while (scanf("%lld %lld", &m, &n) != EOF)
    {
        for (i = 0; i < m; i++)
        {
            scanf("%lld", &datas[i]);
        }
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &x);
            low = 0;
            high = m - 1;
            flag = 0;
            while (low <= high)
            {
                mid = (low + high) / 2;
                if (x == datas[mid])
                {
                    printf("yes\n");
                    flag = 1;
                    break;
                }
                else if (x < datas[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            if (flag == 0)
                printf("no\n");
        }
    }
    return 0;
}
