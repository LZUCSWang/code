#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100 /*�������Ԫ�ظ���*/
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
        printf("�ڴ����ʧ�ܣ�\n");
        exit(0);
    }
    int i;
    printf("���������ݵĴ�Сm(0-100):");
    while (!scanf("%d", &m))
    {
        printf("�����������������(����Ĳ�������):");
        while (getchar() != '\n')
            ;
    };
    while (m <= 0 && m >= MAXSIZE)
    {

        printf("���������ݵĴ�Сm(0-100):"), scanf("%d", &m);
        while (getchar() != '\n')
            ;
    }
    for (i = 0; i < m; printf("����������A�ĵ�%d������Ԫ��", i + 1), scanf("%d", A + i++))
        ;
    for (i = 0; i < m; printf("����������B�ĵ�%d������Ԫ��", i + 1), scanf("%d", B + i++))
        ;
    switch (compare(A, B))
    {
    case BIG:
        printf("����A>B");
        break;
    case SMALL:
        printf("����A<B");
        break;
    case EQUAL:
        printf("����A=B");
        break;
    }
    free(A);
    free(B);
    return 0;
}
int compare(int *A, int *B) /*�Ƚ���������*/
{
    int i;
    for (i = 0; i < m; i++)
        if (A[i] > B[i])
            return BIG; /*������A>B*/
        else if (A[i] < B[i])
            return SMALL; /*������A<B*/
    return EQUAL;         /*������A=B*/
}