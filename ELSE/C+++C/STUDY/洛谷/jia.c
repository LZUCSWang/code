
struct ListNode
{
    int val;
    struct ListNode *next;
}
#include <stdlib.h>
#include <math.h>
struct ListNode *
addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{

    long datas[100], b[100], c[100];
    int i = 0;
    int j = 0;
    struct ListNode *l, *m, *n;
    m = l1;
    n = l2;
    while (l1 != NULL)
    {
        datas[i++] = l1->val;
        l1 = l1->next;
    }
    while (l2 != NULL)
    {
        b[j++] = l2->val;
        l2 = l2->next;
    }
    int a_len = i;
    int b_len = j;
    int num1 = 0, num2 = 0, num, count = 0;
    for (i = 0; i < a_len; i++)
    {
        num1 += datas[i] * pow(10, i);
    }
    for (i = 0; i < b_len; i++)
    {
        num2 += b[i] * pow(10, i);
    }
    num = num1 + num2;
    int temp = num;
    if (num1 == 0 || num2 == 0)
    {
        if (num == 0)
        {
            l = (struct ListNode *)malloc(sizeof(struct ListNode));
            l->val = 0;
            l->next = NULL;
            return l;
        }
        else if (num1 == 0)
        {
            return n;
        }
        else
        {
            return m;
        }
    }
    while (num != 0)
    {
        count++;
        num /= 10;
    }
    struct ListNode *p, *r;
    l = (struct ListNode *)malloc(sizeof(struct ListNode));
    p = r = l;
    l->next = NULL;
    for (i = 0; i < count; i++)
    {
        c[i] = temp % 10;
        temp = temp / 10;
    }

    for (i = 0; i < count; i++)
    {
        p->val = c[i];
        if (i == count - 1)
            break;
        l = (struct ListNode *)malloc(sizeof(struct ListNode));
        l->next = NULL;
        p->next = l;
        p = l;
    }

    return r;
}
