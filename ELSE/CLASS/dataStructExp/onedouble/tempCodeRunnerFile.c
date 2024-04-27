/*设有两个一元多项式A(x),B(x)，请完成运算A(x)+B(x)、
datas(x)-B(x)，要求多项式采用链表结构进行存储，多项式可以按照升幂（降幂）形式输入对应的系数、指数项，但对输入输出格式不做要求。*/
#include <stdio.h>
#include <stdlib.h>
typedef struct xiang //每个项
{
    float x;
    int z;
} xiang;
typedef struct node //链表的结点
{
    xiang data;
    struct node *next;
} node;
node *shuru(FILE *file);
node *jianfa(node *h1, node *h2);
node *chen(node *h1, node *h2);
node *jiafa(node *h1, node *h2);
node *reverse(node *h);
void shuchu(node *h, int x, FILE *fput);
void insert(node *cnth, float tx, int tz);
int main()
{
    FILE *file = fopen("input.txt", "r");
    FILE *fput = fopen("output.txt", "w");
    node *h1;
    node *h2;
    h1 = shuru(file); //从文件里获取多项式
    h2 = shuru(file);
    fclose(file);
    shuchu(jiafa(h1, h2), 1, fput);  //输出加法
    shuchu(jianfa(h1, h2), 2, fput); //输出减法
    shuchu(chen(h1, h2), 3, fput);   //输出乘法
    fclose(fput);
}
node *shuru(FILE *file)
{
    node *h = (node *)malloc(sizeof(node));
    node *temp = (node *)malloc(sizeof(node));
    int b;
    float datas;
    fscanf(file, "%f %d", &datas, &b); //获取系数和指数
    temp->data.x = datas;
    temp->data.z = b;
    temp->next = NULL;
    h->next = temp;

    while (fscanf(file, "%f %d", &datas, &b) == 2 && datas != 0)
    {
        fgetc(file);
        insert(h, datas, b); //将系数和指数插入链表合适位置
    }
    return h;
}
void shuchu(node *h, int x, FILE *fput)
{
    node *p = h->next;
    char datas;
    int cnt = 0;
    switch (x)
    {
    case 1:
        datas = '+';
        break;
    case 2:
        datas = '-';
        break;
    case 3:
        datas = '*';
        break;
    }
    fprintf(fput, "datas(x)%cB(x)=", datas);
    if (p == NULL)
    {
        fprintf(fput, "%c", '0');
    }
    while (p != NULL)
    {
        if (p->data.x == 0)
        {
            p = p->next;
            continue;
        }
        if (cnt != 0)
        {
            if (p->data.x > 0)
                fprintf(fput, "+");
            if (p->data.z == 0)
                fprintf(fput, "%3.1f", p->data.x);
            else if (p->data.x == 1.0)
                fprintf(fput, "X^%d", p->data.z);
            else if (p->data.z == 1)
                fprintf(fput, "%3.1fX", p->data.x);
            else
                fprintf(fput, "%3.1fX^%d", p->data.x, p->data.z);
            p = p->next;
        }
        else
        {
            fprintf(fput, "%3.1fX^%d", p->data.x, p->data.z);
            p = p->next;
            cnt = 1;
        }
    }
    fprintf(fput, "\n");
}
node *jiafa(node *h1, node *h2)
{
    node *p1, *p2, *cnth, *ap;
    cnth = (node *)malloc(sizeof(node));
    p1 = h1->next;
    p2 = h2->next;
    ap = cnth;

    while (p1 != NULL && p2 != NULL)
    {
        node *temp = (node *)malloc(sizeof(node));
        ap->next = temp;
        if (p1->data.z == p2->data.z)
        {
            temp->data.z = p1->data.z;
            temp->data.x = p1->data.x + p2->data.x;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->data.z > p2->data.z)
        {
            temp->data.z = p1->data.z;
            temp->data.x = p1->data.x;
            p1 = p1->next;
        }
        else
        {
            temp->data.z = p2->data.z;
            temp->data.x = p2->data.x;
            p2 = p2->next;
        }
        ap = temp;
    }
    if (p1 == NULL && p2 == NULL)
    {
        ap->next = NULL;
        return cnth;
    }
    if (p1 == NULL)
    {
        while (p2 != NULL)
        {
            node *temp = (node *)malloc(sizeof(node));
            ap->next = temp;
            temp->data.z = p2->data.z;
            temp->data.x = p2->data.x;
            ap = temp;
            p2 = p2->next;
        }
    }
    if (p2 == NULL)
    {
        while (p1 != NULL)
        {
            node *temp = (node *)malloc(sizeof(node));
            ap->next = temp;
            temp->data.z = p1->data.z;
            temp->data.x = p1->data.x;
            ap = temp;
            p1 = p1->next;
        }
    }
    ap->next = NULL;
    return cnth;
}
node *reverse(node *h)
{
    node *pt = h->next;
    while (pt != NULL)
    {
        pt->data.x *= -1;
        pt = pt->next;
    }
    return h;
}
void insert(node *cnth, float tx, int tz)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data.x = tx;
    temp->data.z = tz;
    temp->next = NULL;
    node *cntp = cnth;
    if (cntp->next == NULL)
    {
        cntp->next = temp;
        return;
    }
    while (cntp->next != NULL && cntp->next->data.z > tz)
    {
        cntp = cntp->next;
        if (cntp->next == NULL)
        {
            cntp->next = temp;
            return;
        }
        if (cntp->next->data.z == tz)
        {
            cntp->next->data.x += tx;
            return;
        }
        if (cntp->next->data.z < tz)
        {
            temp->next = cntp->next;
            cntp->next = temp;
            return;
        }
    }
    if (cntp->next != NULL && cntp->next->data.z == tz)
    {
        cntp->next->data.x += tx;
        return;
    }
    else if (cntp->next != NULL && cntp->next->data.z < tz)
    {
        temp->next = cntp->next;
        cntp->next = temp;
        return;
    }
}
node *chen(node *h1, node *h2)
{
    node *cnth = (node *)malloc(sizeof(node));
    cnth->next = NULL;
    node *p1 = h1->next, *p2 = h2->next;
    while (p1 != NULL)
    {
        p2 = h2->next;
        while (p2 != NULL)
        {
            int tz;
            float tx;
            tx = p1->data.x * p2->data.x;
            tz = p1->data.z + p2->data.z;
            insert(cnth, tx, tz);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return cnth;
}
node *jianfa(node *h1, node *h2)
{
    h2 = reverse(h2);
    node *temp = jiafa(h1, h2);
    h2 = reverse(h2);
    return temp;
}