#include <stdio.h>
#include <stdlib.h>
typedef struct linklist
{
    int data[100];
    int length;
} linklist;
void jiaoji(linklist *L, linklist *L1, linklist *L2, int n, int m);
int main()
{
    linklist *L, *L1, *L2;
    L = (linklist *)malloc(sizeof(linklist));
    L1 = (linklist *)malloc(sizeof(linklist));
    L2 = (linklist *)malloc(sizeof(linklist));
    int n, m, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &(L1->data[i]));
    scanf("%d", &m);
    for (i = 0; i < m; i++)
        scanf("%d", &(L2->data[i]));
    jiaoji(L, L1, L2, n, m);
    return 0;
}
void jiaoji(linklist *L, linklist *L1, linklist *L2, int n, int m)
{
    int k = 0, i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (L1->data[i] == L2->data[j])
            {
                L->data[k] = L1->data[i];
                k++;
            }
        }
    }
    if (k == 0)
    {
        printf("\n");
    }
    else
    {
        for (i = 0; i < k; i++)
        {
            printf("%d ", L->data[i]);
        }
    }
}
