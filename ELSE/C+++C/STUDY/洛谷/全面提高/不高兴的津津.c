#include <stdio.h>
int main()
{
    int datas, b, cnt = 0;
    int mt = 0;
    for (int i = 1; i <= 7; i++)
    {
        scanf("%d %d", &datas, &b);
        int t = datas + b;
        if (t > 8 && t > mt)
        {
            mt = t;
            cnt = i;
            // printf("%d", mt);
        }
    }
    printf("%d", cnt);
}