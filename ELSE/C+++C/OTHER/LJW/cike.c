#include <stdio.h>
int main()
{
    int c, f;
    scanf("%d %d", &c, &f);
    int all = (c + f) / 4;
    if (all < c)
        if (all < f)
            printf("%d", all);
        else
            printf("%d", f);
    else if (f < c)
        printf("%d", f);
    else printf("%d",all<f?all:f);
}