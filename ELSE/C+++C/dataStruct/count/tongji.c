#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct node
{
    int times, row, col;
    char string[100];
    struct node *next;
} node;
void print(node *head, int alltimes) //输出结果
{
    FILE *f = fopen("output.txt", "w");
    node *p = head;
    fprintf(f, "word\t           row \t  col\ttimes\tpinlv %d(total)\n", alltimes);
    while (p != NULL)
    {
        fprintf(f, "%-20s%-5d %-5d %-5d %-5.5f%%\n", p->string, p->row, p->col, p->times, p->times / (alltimes * 1.0) * 100);
        p = p->next;
    }
    fclose(f);
}
void deal(char *temp, node *head, int row, int col, int *alltimes, node **p) //加入的同时字典序排序
{
    (*alltimes)++;
    node *t = head->next;
    node *save = head;
    while (t != NULL) //遍历链表
    {
        if (strcmp(t->string, temp) == 0) //如果存在相同的字符串
        {
            t->times++;
            return;
        }
        if (strcmp(save->string, temp) < 0 && strcmp(t->string, temp) > 0) //插入的同时按字典序排序
        {
            node *n = (node *)malloc(sizeof(node));
            strcpy(n->string, temp);
            // free(temp);
            n->times = 1;
            n->row = row;
            n->col = col;
            n->next = t;
            save->next = n;
            return;
        }
        save = t;
        t = t->next;
    }
    (*p)->next = (node *)malloc(sizeof(node)); //最大则尾插
    *p = (*p)->next;
    strcpy((*p)->string, temp);
    (*p)->times = 1;
    (*p)->row = row;
    (*p)->col = col;
    (*p)->next = NULL;
}
int main()
{

    FILE *f = fopen("input.txt", "r");
    node *p, *head = (node *)malloc(sizeof(node));
    p = head;
    strcpy(head->string, "");
    head->next = NULL;
    char temp[100], t;
    int row = 1, col = 1, alltimes = 0;
    int flag = 0;
    int k = 0;
    while (1)
    {
        t = fgetc(f);
        if (t == EOF) //结束
        {
            if (strlen(temp) != 0) //最后还有一个
                deal(temp, head, row, col, &alltimes, &p);
            break;
        }
        if (t == '\n') //换行
        {
            row++;
            col = 1;
        }
        if (isalpha(t)) //字母
        {
            t = tolower(t);
            temp[k++] = t; //加入缓存
            flag = 1;      //标志在子母中
            continue;
        }
        if (isalpha(t) == 0 && flag) //非字母且之前有字母
        {
            temp[k] = '\0';
            deal(temp, head, row, col, &alltimes, &p); //加入
            if (t != '\n')
                col++;
            k = 0;
            flag = 0;
        }
    }
    print(head->next, alltimes); //输出
    fclose(f);
}