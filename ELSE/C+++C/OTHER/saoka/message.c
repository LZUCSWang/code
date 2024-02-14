#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define MW 100
typedef struct Qnode
{
    char data[MW];//字符数组存储短信
    struct Qnode *next;
} Qnode;//定义队列的结点

Qnode *head = NULL;//头指针
Qnode *rear = NULL;//尾指针
int cnt = 0;//记录短信信息
void add_my_message()//添加信息
{
    Qnode *p = (Qnode *)malloc(sizeof(Qnode));//新建结点
    printf("Please input the message:");
    fgets(p->data, MW, stdin);//读取一行字符串作为信息
    if (head)
        p->next = head;
    else
    {
        p->next = NULL;
    }
    head = p;
    if (++cnt >= MAX)//如果超出了最大的存储
    {
        Qnode *q = head;
        while (q->next != rear)//遍历到尾指针
            q = q->next;
        q->next = NULL;//将尾指针指向的结点清空回收空间
        free(rear);
        rear = q;
        cnt--;
    }
}
void show_all_my_message()//展示所有的信息
{
    Qnode *p = head;
    while (p != NULL)//遍历整个队列
    {
        printf("%s\n", p->data);//输出信息
        p = p->next;
    }
}
void show_any_of_my_message()//展示特定位置的信息
{
    int n;
    printf("Please input the number of message:");
    scanf("%d", &n);
    Qnode *p = head;
    while (p != NULL && n > 1)//往后循环，n不断自减计数
    {
        n--;
        p = p->next;
    }
    printf("%s\n", p->data);
}
void delete_any_of_my_message()
{
    int n;
    printf("please input the number of message:");
    scanf("%d", &n);
    Qnode *p = head;
    if(n==1){//如果要删掉第一个点，较为特殊，需要改变head的值，特殊处理
        head=p->next;
        printf("you have deleted %s\n", p->data);
        free(p);
        return;
    }
    n--;
    while (p->next != NULL && n > 1)//如果要删去的结点大于等于2，那就往后循环并遍历，n自减计数，其中p->next为要删去的结点
    {
        n--;
        p = p->next;
    }
    Qnode *q = p->next;
    p->next = q->next;//删去结点之前先连接好前后
    printf("you have deleted %s\n", q->data);
    free(q);
}
void clear_my_message()//全部清空
{
    Qnode *p = head;
    while (p != NULL)
    {
        Qnode *q = p;
        p = p->next;
        free(q);
    }
    head = NULL;
    rear = NULL;
    cnt = 0;
}
void message_function()
{
    int choice;
    printf("1.add message\n2.show all message\n3.show any message\n4.delete any message\n5.clear my message\n6.exit\n");
    while (scanf("%d", &choice))
    {
        getchar();
        switch (choice)
        {
        case 1:
            add_my_message();
            break;
        case 2:
            show_all_my_message();
            break;
        case 3:
            show_any_of_my_message();
            break;
        case 4:
            delete_any_of_my_message();
            break;
        case 5:
            clear_my_message();
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("input error!\n");
            break;
        }
        printf("1.add message\n2.show all message\n3.show any message\n4.delete any message\n5.clear my message\n6.exit\n");
    }
}
int main()
{
    message_function();
}
