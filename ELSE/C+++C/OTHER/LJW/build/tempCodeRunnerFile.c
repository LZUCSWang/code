#include <stdio.h>
int main()
{
    int len, wid, i, j, k;
    scanf("%d %d", &len, &wid);
    int arry[len][wid];
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < wid; j++)
        {
            scanf("%d", &arry[i][j]);
        }
    }
    int times, lx, ly, rx, ry, sum = 0;
    scanf("%d", &times);
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
}