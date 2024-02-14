#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define ElemType int
#define MAX_SIZE 1000
typedef struct
{
    int row;//���±�
    int col;//���±�
    ElemType value;//Ԫ��ֵ
}Triple;
typedef struct
{
    int m;//����
    int n;//����
    int t;//��0Ԫ�ظ���
    Triple data[MAX_SIZE];
}TMatrix;
void create_matrix(TMatrix *s,int M,int N)//��������
{
    (*s).m=M;(*s).n=N;
    printf("�����0Ԫ�صĸ�����");
    scanf_s ("%d",&(*s).t);
    for(int i=1;i<=(*s).t;i++)
    {
        printf("�����%d����0Ԫ�ص������������Լ���ֵ��",i);
        scanf_s ("%d%d%d",&(*s).data[i].row,&(*s).data[i].col,&(*s).data[i].value);
    }
}
void add_matrix(TMatrix a,TMatrix b,TMatrix *c)//�������
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
                (*c).data[temp].value=b.data[j].value;//С�ĸ���c
                (*c).t++;//����Ԫ�ؼ�һ
                temp++;j++;
            }
            else if(a.data[i].row<b.data[j].row)
            {
                (*c).data[temp].row=a.data[i].row;
                (*c).data[temp].col=a.data[i].col;
                (*c).data[temp].value=a.data[i].value;//С�ĸ���c
                (*c).t++;//����Ԫ�ؼ�һ
                temp++;i++;
            }
            else //�к����
            {
                if(a.data[i].col>b.data[j].col)
                {
                    (*c).data[temp].row=b.data[j].row;
                    (*c).data[temp].col=b.data[j].col;
                    (*c).data[temp].value=b.data[j].value;//С�ĸ���c
                    (*c).t++;//����Ԫ�ؼ�һ
                    temp++;j++;
                }
                else if(a.data[i].col<b.data[j].col)
                {
                    (*c).data[temp].row=a.data[i].row;
                    (*c).data[temp].col=a.data[i].col;
                    (*c).data[temp].value=a.data[i].value;//С�ĸ���c
                    (*c).t++;//����Ԫ�ؼ�һ
                    temp++;i++;
                }
                else //�к�Ҳ���
                {
                    (*c).data[temp].row=a.data[i].row;
                    (*c).data[temp].col=a.data[i].col;
                    (*c).data[temp].value=a.data[i].value+b.data[j].value;//�ӺͲ�����c
                    (*c).t++;//����Ԫ�ؼ�һ
                    temp++;i++;j++;
                }
            }
        }
}
void disp_matrix(TMatrix s)//������ʾ
{
    ElemType A[(s.m)+1][(s.n)+1];
	memset(A,0,sizeof(A));//�����ά���飬��ʹ��ʼֵ��Ϊ0
    for(int temp=1;temp<=s.t;temp++)//��0Ԫ�ؽ�������
        A[s.data[temp].row][s.data[temp].col]=s.data[temp].value;
    for(int i=1;i<=s.m;i++)//��ʾ�����ľ���
    {
        for(int j=1;j<=s.n;j++)
            printf(" %d",A[i][j]);
        printf("\n");
    }
}
int main()
{
    TMatrix a,b,c;
    int M,N;//m:���� n:����
    printf("�������������");scanf("%d",&M);
    printf("�������������");scanf("%d",&N);
    printf("��������a��");create_matrix(&a,M,N);
    printf("�����ľ���a��\n");disp_matrix(a);
    printf("��������b��");create_matrix(&b,M,N);
    printf("�����ľ���b��\n");disp_matrix(b);
    add_matrix(a,b,&c);
 
    printf("����Ԫ�ؾ���c������Ԫ�ع���%d��\n���±� ���±� Ԫ��ֵ\n",c.t);
    for(int i=1;i<=c.t;i++)
        printf("  %d      %d      %d\n",c.data[i].row,c.data[i].col,c.data[i].value);
 
    printf("�����ľ���c��\n");disp_matrix(c);
    return 0;
}
