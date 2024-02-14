#include <stdio.h>
#define N 100
int main()
{
    /********** Begin **********/
    int datas[N], t = 0, b = 0, i, max, min, n, x;
    for (i = 0; i < N; i++)
    {
        scanf("%d", &datas[i]);
        if (datas[i] == 0)
            break;
    }
    n = i;
    max = datas[0];
    min = datas[0];
    for (i = 1; i < n; i++)
    {
        if (max < datas[i])
        {
            max = datas[i];
            t = i;
        }
        if (min > datas[i])
        {
            min = datas[i];
            b = i;
        }
    }
    printf("max:%d,index:%d\n", max, t);
    printf("max:%d,index:%d\n", min, b);
    x = datas[t];
    datas[t] = datas[b];
    datas[b] = x;
    for (i = 0; i < n; i++)
    {
        printf("%d ", datas[i]);
    }

    /********** End **********/
    return 0;
}
