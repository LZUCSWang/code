#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define ElemType int
#define MAX_SIZE 1000
typedef struct
{
    int row;//行下标
    int col;//列下标
    ElemType value;//元素值
}Triple;
typedef struct
{
    int m;//行数
    int n;//列数
    int t;//非0元素个数
    Triple data[MAX_SIZE];
}TMatrix;
void create_matrix(TMatrix *s,int M,int N)//创建矩阵
{
    (*s).m=M;(*s).n=N;
    printf("输入非0元素的个数：");
    scanf_s ("%d",&(*s).t);
    for(int i=1;i<=(*s).t;i++)
    {
        printf("输入第%d个非0元素的行数、列数以及数值：",i);
        scanf_s ("%d%d%d",&(*s).data[i].row,&(*s).data[i].col,&(*s).data[i].value);
    }
}
void add_matrix(TMatrix a,TMatrix b,TMatrix *c)//矩阵相加
{
    int temp=1;
    (*c).m=a.m;(*c).n=a.n;
    (*c).t=0;
    for(int i=1;i<=a.t;)
        for(int j=1;j<=b.t;)
        {
            if(a.data[i].row>b.data[j].row)
            {
                (*c).data[temp].row=b.data[j].row;
                (*c).data[temp].col=b.data[j].col;
                (*c).data[temp].value=b.data[j].value;//小的给到c
                (*c).t++;//非零元素加一
                temp++;j++;
            }
            else if(a.data[i].row<b.data[j].row)
            {
                (*c).data[temp].row=a.data[i].row;
                (*c).data[temp].col=a.data[i].col;
                (*c).data[temp].value=a.data[i].value;//小的给到c
                (*c).t++;//非零元素加一
                temp++;i++;
            }
            else //行号相等
            {
                if(a.data[i].col>b.data[j].col)
                {
                    (*c).data[temp].row=b.data[j].row;
                    (*c).data[temp].col=b.data[j].col;
                    (*c).data[temp].value=b.data[j].value;//小的给到c
                    (*c).t++;//非零元素加一
                    temp++;j++;
                }
                else if(a.data[i].col<b.data[j].col)
                {
                    (*c).data[temp].row=a.data[i].row;
                    (*c).data[temp].col=a.data[i].col;
                    (*c).data[temp].value=a.data[i].value;//小的给到c
                    (*c).t++;//非零元素加一
                    temp++;i++;
                }
                else //列号也相等
                {
                    (*c).data[temp].row=a.data[i].row;
                    (*c).data[temp].col=a.data[i].col;
                    (*c).data[temp].value=a.data[i].value+b.data[j].value;//加和并给到c
                    (*c).t++;//非零元素加一
                    temp++;i++;j++;
                }
            }
        }
}
void disp_matrix(TMatrix s)//矩阵显示
{
    ElemType A[(s.m)+1][(s.n)+1];
	memset(A,0,sizeof(A));//定义二维数组，并使初始值均为0
    for(int temp=1;temp<=s.t;temp++)//非0元素进入数组
        A[s.data[temp].row][s.data[temp].col]=s.data[temp].value;
    for(int i=1;i<=s.m;i++)//显示完整的矩阵
    {
        for(int j=1;j<=s.n;j++)
            printf(" %d",A[i][j]);
        printf("\n");
    }
}
int main()
{
    TMatrix a,b,c;
    int M,N;//m:行数 n:列数
    printf("输入矩阵行数：");scanf("%d",&M);
    printf("输入矩阵列数：");scanf("%d",&N);
    printf("创建矩阵a：");create_matrix(&a,M,N);
    printf("完整的矩阵a：\n");disp_matrix(a);
    printf("创建矩阵b：");create_matrix(&b,M,N);
    printf("完整的矩阵b：\n");disp_matrix(b);
    add_matrix(a,b,&c);
 
    printf("非零元素矩阵c：非零元素共有%d个\n行下标 列下标 元素值\n",c.t);
    for(int i=1;i<=c.t;i++)
        printf("  %d      %d      %d\n",c.data[i].row,c.data[i].col,c.data[i].value);
 
    printf("完整的矩阵c：\n");disp_matrix(c);
    return 0;
}
