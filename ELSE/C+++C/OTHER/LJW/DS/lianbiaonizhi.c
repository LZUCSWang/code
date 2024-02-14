#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
} node;
void show(node *h)
{
    node *p = h->next;
    while (p != h)
    {
        printf("%d ", h->data);
        h = h->next;
    }
    printf("\n");
}
node *reverse(node *h)
{
    node *p, *t1, *t;
    p = h;
    t1 = p->next;
    p->next = NULL;
    if (t1 != NULL)
    {
        t = t1->next;
        while (t != NULL)
        {
            t1->next = p;
            p = t1;
            t1 = t;
            t = t->next;
        }
        t1->next = p;
        return t1;
    }
    return h;
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
    p->next = h;
}
int main()
{
    node *h1 = getint();
    node *h2 = getint();
    show(h1);
    show(h2);
}
