#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100 /*最大数组元素个数*/
#define BIG 1
#define SMALL -1
#define EQUAL 0
int m;
int compare(int *A, int *B);
int main()
{
    int *A, *B;
    A = (int *)malloc(MAXSIZE * sizeof(int));
    B = (int *)malloc(MAXSIZE * sizeof(int));
    if (A == NULL || B == NULL)
    {
        printf("内存分配失败！\n");
        exit(0);
    }
    int i;
    printf("请输入数据的大小m(0-100):");
    while (!scanf("%d", &m))
    {
        printf("输入错误，请重新输入(输入的不是数字):");
        while (getchar() != '\n')
            ;
    };
    while (m <= 0 && m >= MAXSIZE)
    {

        printf("请输入数据的大小m(0-100):"), scanf("%d", &m);
        while (getchar() != '\n')
            ;
    }
    for (i = 0; i < m; printf("请输入数组A的第%d个数组元素", i + 1), scanf("%d", A + i++))
        ;
    for (i = 0; i < m; printf("请输入数组B的第%d个数组元素", i + 1), scanf("%d", B + i++))
        ;
    switch (compare(A, B))
    {
    case BIG:
        printf("数组A>B");
        break;
    case SMALL:
        printf("数组A<B");
        break;
    case EQUAL:
        printf("数组A=B");
        break;
    }
    free(A);
    free(B);
    return 0;
}
int compare(int *A, int *B) /*比较数组数据*/
{
    int i;
    for (i = 0; i < m; i++)
        if (A[i] > B[i])
            return BIG; /*返回在A>B*/
        else if (A[i] < B[i])
            return SMALL; /*返回在A<B*/
    return EQUAL;         /*返回在A=B*/
}