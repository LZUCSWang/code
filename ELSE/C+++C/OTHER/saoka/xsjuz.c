#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct // 三元组元素的存储结构
{
    int i, j;
    int v;
} node;
typedef struct // 稀疏矩阵的存储结构
{
    int m, n, t; // 行 列 个数
    node data[MAXSIZE];
} TSMatrix;
void SpmInit(TSMatrix *s) // 稀疏矩阵的初始化
{
    int i;
    printf("请输入行数 列数 个数(逗号隔开):\n");
    scanf("%d,%d,%d", &s->m, &s->n, &s->t);
    printf("请输入数据元素:\n");
    for (i = 0; i < s->t; i++)
    {
        scanf("%d,%d,%d", &s->data[i].i, &s->data[i].j, &s->data[i].v);
    }
}
void TSMatris_Add(TSMatrix *a, TSMatrix *b, TSMatrix *c)
{
    int i = 0, j = 0, j1 = 0, j2 = 0; // j j1 j2 分别指向C A B的当前元素
    c->m = a->m;                      // 将三元组a的属性赋予给A&B
    c->n = a->n;
    c->t = a->t + b->t;
    for (i = 0; i < c->t; i++)
    {
        if (j1 > a->t && j2 < b->t) // 如果a已经读完,b未读完,则将b后面的全部赋给c
        {
            c->data[j] = b->data[j2];
            j2++;
            j++;
        }
        else if (j1 < a->t && j2 > b->t) // 如果b已经读完,a未读完,则将a后面的全部赋给c
        {
            c->data[j] = a->data[j1];
            j1++;
            j++;
        }
        else if (j1 >= a->t && j2 >= b->t) // ab都已经扫描完,循环退出
        {
            break;
        }
        else                                   // 否则进行扫描操作
        {                                      // 先比较行号
            if (a->data[j1].i > b->data[j2].i) // 如果a的函数大于b的行数,则将b的此行赋给c
            {
                c->data[j] = b->data[j2];
                j2++;
                j++;
            }
            else if (a->data[j1].i < b->data[j2].i) // 如果b的函数大于a的行数,则将a的此行赋给c
            {
                c->data[j] = a->data[j1];
                j1++;
                j++;
            }
            else // 则行号相等,比较列号
            {

                if (a->data[j1].j > b->data[j2].j) // 如果a的列数大于b的列数,则将b赋给c
                {
                    c->data[j] = b->data[j2];
                    j2++;
                    j++;
                }
                else if (a->data[j1].j < b->data[j2].j) // 如果b的列数大于a的行数,则将a赋给c
                {
                    c->data[j] = a->data[j1];
                    j1++;
                    j++;
                }
                else // 否则相等,此位置两个矩阵均有元素
                {
                    if ((a->data[j1].v) + (b->data[j2].v) == 0) // 如果a b相加为0,忽略继续循环
                    {
                        j1++;
                        j2++;
                    }
                    else
                    {
                        c->data[j] = a->data[j1];
                        c->data[j].v = (a->data[j1].v) + (b->data[j2].v);
                        j1++;
                        j2++;
                        j++;
                    }
                }
            }
        }
    }
    c->t = j; // 元素个数为最后退出是j的计数值
}
void print(TSMatrix *s)
{
    int i = 0;
    for (i; i < s->t; i++)
    {
        printf("%3d%3d%3d\n", s->data[i].i, s->data[i].j, s->data[i].v);
    }
}
int main()
{
    TSMatrix *a, *b, *c;
    a = (TSMatrix *)malloc(sizeof(TSMatrix));
    b = (TSMatrix *)malloc(sizeof(TSMatrix));
    c = (TSMatrix *)malloc(sizeof(TSMatrix));
    SpmInit(a);
    SpmInit(b);
    TSMatris_Add(a, b, c);
    print(a);
    printf("\n");
    print(b);
    printf("\n");
    printf("%d", c->t);
    printf("\n");
    print(c);
}
