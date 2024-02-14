#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    char data;
    struct node *next;
} node;
node *reverse(node *head)
{
    node *p, *q, *r;
    p = head;
    q = p->next;
    r = q->next;
    while (r != NULL)
    {
        q->next = p;
        p = q;
        q = r;
        r = r->next;
    }
    q->next = p;
    head->next = NULL;
    return q;
}
void print(node *head)
{
    node *p;
    p = head;
    while (p != NULL)
    {
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}
int main()
{
    node *head, *p;
    int i;
    head = (node *)malloc(sizeof(node));
    p = head;
    scanf("%c", &head->data);
    char temp;
    while (1)
    {
        scanf("%c", &temp);
        if (temp == '\n')
            break;
        p->next = (node *)malloc(sizeof(node));
        p->next->data = temp;
        p = p->next;
    }
    p->next = NULL;
    print(reverse(head));
    return 0;
}
