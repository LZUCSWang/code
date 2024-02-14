#include <bits/stdc++.h>
using namespace std;
#define N 10000000
int a[N], b[N];
int main()
{
    getchar();
    int i = 0;
    while (1)
    {
        scanf("%d", &a[i++]);
        if (getchar() == ',')
            continue;
        else
            break;
    }
    getchar();
    getchar();
    int j = 0;
    while (1)
    {
        scanf("%d", &b[j++]);
        if (getchar() == ',')
            continue;
        else
            break;
    }
    printf("[");
    for (i = 0; i < j; i++)
    {
        printf("%d,%d", a[i], b[i]);
        if (i != j - 1)
            printf(",");
        else
            printf("]");
    }
}