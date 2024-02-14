#include <stdio.h>
#define N 10000
int main()
{
    int i = 0, j = 0, al[N], bl[N], datas, b;
    /********** Begin *********/
    //存
    scanf("%d", &datas);
    for (; i < datas; i++)
    {
        scanf("%d", &al[i]);
    }
    scanf("%d", &b);
    for (; j < b; j++)
    {
        scanf("%d", &bl[j]);
    }
    //交换
    int min = datas < b ? datas : b;
    for (i = 0; i < min; i++)
    {
        int temp = al[i];
        al[i] = bl[i];
        bl[i] = temp;
    }
    if (datas != b)
    {
        if (datas < b)
            for (i = min; i < b; i++)
                al[i] = bl[i];
        else
            for (i = min; i < datas; i++)
                bl[i] = al[i];
    }
    int t = datas;
    datas = b;
    b = t;
    //输出
    for (i = 0; i < datas; i++)
        printf("%d ", al[i]);
    putchar('\n');
    for (i = 0; i < b; i++)
        printf("%d ", bl[i]);

    /********** End **********/
    return 0;
}
