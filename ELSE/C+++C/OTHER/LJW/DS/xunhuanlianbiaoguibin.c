#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
} node, *linklist;
void show(node *h)
{
    h = h->next;
    while (h != NULL)
    {
        printf("%d ", h->data);
        h = h->next;
    }
    printf("\n");
}
node *getint()
{
    int n;
    node *h = (node *)malloc(sizeof(node)), *p = h;
    h->next = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        node *t = (node *)malloc(sizeof(node));
        scanf("%d", &(t->data));
        t->next = NULL;
        p->next = t;
        p = t;
    }
    return h;
}
void MergeList_L(linklist *h1, linklist *h2)
{
    node *h11 = *h1, *h22 = (*h2)->next;
    node *save;
    while (h11 != NULL && h22 != NULL)
    {
        if (h22->data == h11->next->data)
        {
            h22 = h22->next;
            continue;
        }
        while (h22 && h22->data < h11->next->data)
        {
            save = h22->next;
            h22->next = h11->next;
            h11->next = h22;
            h11 = h22;
            h22 = save;
        }
        h11 = h11->next;
        if (h11->next == NULL)
        {
            h11->next = h22;
            break;
        }
    }
}
int main()
{
    node *h1 = getint();
    node *h2 = getint();
    MergeList_L(&h1, &h2);
    show(h1);
}
