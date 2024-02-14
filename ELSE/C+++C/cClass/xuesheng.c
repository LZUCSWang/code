#include <stdio.h>
#include <stdlib.h>
#define JIEDIAN                               \
    printf("Enter num and grade\n");          \
    node *new = (node *)malloc(sizeof(node)); \
    scanf("%d %d %d %d %s", &new->num, &new->chinese, &new->math, &new->english, new->name);
typedef struct node
{
    int num;
    char name[10];
    int chinese, math, english;
    struct node *next;
} node;
int charuend(node *head)
{
    JIEDIAN
    node *p = head;
    while (1)
    {
        p = p->next;
        if (p->next == NULL)
        {
            p->next = new;
            new->next = NULL;
            return 0;
        }
    }
    return -1;
}
int charustart(node *head)
{
    JIEDIAN
    node *p = head;
    new->next = p->next;
    p->next = new;
    return 0;
}
int charubynum(node *head)
{
    int n;
    scanf("%d", &n);
    JIEDIAN
    node *p = head;
    while (p->next && p->next->num != n)
    {
        p = p->next;
    }
    new->next = p->next;
    p->next = new;
    return 0;
}
int shuchu(node *head)
{
    node *p = head->next;
    while (p)
    {
        printf("num : %2d name : %s\tchinese : %2d math : %2d english : %2d\n", p->num, p->name, p->chinese, p->math, p->english);
        p = p->next;
    }
    return 0;
}
int delete (node *head)
{
    int n;
    scanf("%d", &n);
    node *p = head;
    while (p->next && p->next->num != n)
    {
        p = p->next;
    }
    node *clear = p->next;
    p->next = p->next->next;
    free(clear);
    return 0;
}
int main()
{
    char tempname[10];
    int times;
    scanf("%d", &times);
    node *head = (node *)malloc(sizeof(node));
    node *p = head;
    for (int i = 0; i < times; i++)
    {
        node *new = (node *)malloc(sizeof(node));
        printf("input num and grades\n");
        scanf("%d %d %d %d %s", &new->num, &new->chinese, &new->math, &new->english, new->name);
        p->next = new;
        new->next = NULL;
        p = new;
    }
    shuchu(head);
    int choice;
    printf("1)charustart\t2)charuend\n3)charubynum\t4)delete\n");
    while (scanf("%d", &choice))
    {
        switch (choice)
        {
        case 1:
            charustart(head);
            break;
        case 2:
            charuend(head);
            break;
        case 3:
            charubynum(head);
            break;
        case 4:
            delete (head);
            break;
        default:
            printf("Enter arror");
            break;
        }
        shuchu(head);
    }
}
