#include <stdio.h>
int main()
{
    int len, wid, i, j, k;
    scanf("%d %d", &len, &wid);
    int arry[len][wid];
    for (i = 0; i < len * wid; i++)
    {
        scanf("%d", &arry[i / wid][i % wid]);
    }
    int times, lx, ly, rx, ry, sum = 0;
    scanf("%d", &times);
    if (times <= 20)
        for (i = 0; i < times; i++)
        {
            scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
            for (j = lx; j <= rx; j++)
            {
                for (k = ly; k <= ry; k++)
                {
                    sum += arry[j][k];
                }
            }
            printf("%d\n", sum);
            sum = 0;
        }
    else
    {
        int sum[len + 1][wid + 1];
        for (i = 0; i < len + 1; i++)
        {
            for (j = 0; j < wid + 1; j++)
            {
                sum[i][j] = 0;
                printf("%d\n", sum[i][j]);
            }
        }
        //printf("%d*%d*%d*",sum[0][0],sum[0][1],sum[1][0]);
        for (int i = 1; i <= len; i++)
        {
            for (int j = 1; j <= wid; j++)
            {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arry[i - 1][j - 1];
            }
        }
        for (int m = 0; m < times; m++)
        {
            scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
            lx++, ly++, rx++, ry++;
            printf("%d\n", sum[rx][ry] - sum[lx - 1][ry] - sum[rx][ly - 1] + sum[lx - 1][ly - 1]);
        }
    }
}