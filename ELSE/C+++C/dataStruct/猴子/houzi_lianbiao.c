#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int value;         //节点的值
    int live;          //节点存活或死亡
    struct node *next; //指针域
} node;
node *next_step(node *p, int n)
{ //找到下一个节点
    for (int i = 0; i < n - 1; i++)
    { //移动n-1布
        p = p->next;
        while (p->live == 0)
        { //遇到死节点找下一个
            p = p->next;
        }
    }
    return p;
}
void clear(node *h)
{
    node *last = h;
    while (h != NULL)
    {
        h = h->next;
        free(last);
        last = h;
    }
}
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    node *p = (node *)malloc(sizeof(node)); //为头节点分配空间
    node *head = p;
    head->live = 1;
    head->value = 1;
    for (int i = 2; i <= m; i++)
    { //创建链表
        node *temp = (node *)malloc(sizeof(node));
        p->next = temp;
        temp->value = i;
        temp->live = 1;
        p = temp;
    }
    p->next = head; //使得链表循环
    p = head;
    int cnt = 0;
    while (1 > 0)
    {                        //循环
        cnt++;               //计数
        p = next_step(p, n); //找到对应下一个淘汰的节点地址
        p->live = 0;         //标记它已被淘汰
        p = p->next;         //指向下一个
        while (p->live == 0)
        { //直到指到没有被淘汰的节点为止
            p = p->next;
        }
        if (cnt == m - 1)
        {                           //淘汰m-1个以后
            printf("%d", p->value); //输出值
            return 0;
        }
    }
}