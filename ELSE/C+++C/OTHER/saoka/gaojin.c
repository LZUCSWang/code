#include "stdio.h"
#include "string.h"
#define N 1000//���ں��ڴ���
#include <stdlib.h>
 
 
void csh()
{
    
printf("\t\t\t\t------��λ�㷨--------\n"
 
       "\t\t\t\t|     �ӷ�:1         |\n"
       
       "\t\t\t\t|     ����:2         |\n"
       
       "\t\t\t\t|     �˷�:3         |\n"
       
        "\t\t\t\t|   �������:4       |\n"
        
       "\t\t\t\t|    ���¿�ʼ:0      |\n"
       
       "\t\t\t\t----------------------      ");
 
}
 
void abc()
//�������� 
{
	system("cls");
	//����cmd����������Ļ 
	
	csh();	
	//����csh���� 
	
}
 
void HighPlus(char x1[], char x2[]);
void HighMinus(char x1[], char x2[]);
void HighMultiply(char x1[], char x2[]);
void Output(int a[], int n);
int compare(char a[], char b[]);
 
 
 
int main()  // main������ʼ���� 
{
csh();  //��ʼ��Ļ 
  int a,b,sf=1,js;
  //����ֵ
  //�Է����� 
 char x1[N], x2[N];
 
 
 
for(int i=1;i<=1000;i++)
{
	
	
 
 
if(a==4)
{
	break;
	
	//����Ϊ4�Ļ���ֱ�ӽ������� 
}
 
 
 
//��ӡ�㷨���	
printf("\n�������㷨���:");
 
 
//������룬�������к� 
 
scanf("%d",&a);
// 
 
 
while(1)
{
  
    if(a<=0||a>=5) 
	//�ж��Ƿ���0��4���ڵ� 
    
    {
    	if(a==0)  
		//����Ϊ0�Ļ��� ֱ�ӵ�����������������Ļ 
		
    {
    	abc();
    	
  		break;
  		//��������Ļ֮�����¿�ʼ��һ�ִ�ӡ������� 
	}
	
 
    		
    	
        printf("\n������������������㷨����");
        //��ʾ�����ֵ���� 
        break;
        //������һ���ж� 
    }
    
    
   	if(a==4)  
	   //����Ϊ4����ͽ��� 
	   
	{
		
		break;
		 //������һ���ж� 
		 
	}
    
 
    
    printf("\n������ֵ�ÿո����:\n");
//    gets(x1);//��֤��������ֿ���Ϊ�߾���
//	gets(x2);
scanf("%s %s",&x1,&x2);
   
    
   
switch(a) 
 //�ж�ֵ 
{
    case 1: 
	HighPlus(x1, x2); 
	 //���üӷ��������ɹ��ͽ��� 
		break;
		
    
    case 2: HighMinus(x1, x2);
	//���ü����������ɹ��ͽ��� 
		break;
		
    
    case 3: HighMultiply(x1, x2);
	//���ó˷��������ɹ��ͽ��� 
		break;
		
 
    default : break;  
	//�������������ѭ�� 
 }
    
 
printf("\n\n\t\t>>�Ƿ����(1/0)<<:");
//��ӡ�ж��Ƿ������
 
scanf("%d",&sf);
//���sf��ֵ 
 
 
if(sf==0)  
  //��������ֵΪ0������ѭ�� 
 {
 	
break;
 
 }
    
 
    
} 
 
}
 
printf("\t\t\n""<�������>""");
//�������������
//goob bai! 
 
return 0;   
 
//������� 
}
 
void HighPlus(char x1[], char x2[])
{
	int i, j, n, n1 = strlen(x1), n2 = strlen(x2);
	int a[N] = { 0 }, b[N] = { 0 };
	for (i = n1 - 1, j = 0; i >= 0; i--)
		a[j++] = x1[i] - '0';		//�ַ�ת����
	for (i = n2 - 1, j = 0; i >= 0; i--)
		b[j++] = x2[i] - '0';		//�ַ�ת����
	if (n1 > n2)
		n = n1;
	else						//ȡ��λ��
		n = n2;
	for (i = 0; n > i; i++)
	{
		a[i] += b[i];
		a[i + 1] += a[i] / 10;		//��λ���ӷ�
		a[i] = a[i] % 10;
	}
	if (a[n] != 0)
		n = n + 1;			//������λ��λ��λ����һ
	Output(a, n);
}
void HighMinus(char x1[], char x2[])
{
	int i, j = 0, n, n1 = strlen(x1), n2 = strlen(x2);
	int a[N] = { 0 }, b[N] = { 0 };
	for (i = n1 - 1, j = 0; i >= 0; i--)
		a[j++] = x1[i] - '0';		//�ַ�ת����
	for (i = n2 - 1, j = 0; i >= 0; i--)
		b[j++] = x2[i] - '0';		//�ַ�ת����
	if (compare(x1, x2) == 1)		//�ж�˭��˭С
	{
		n = n1;
		for (i = 0; n > i; i++)
		{
			a[i] -= b[i];
			if (a[i] < 0)				//��λ������
				a[i] += 10, a[i + 1]--;
		}
		while (a[n - 1] == 0)		//ȥ��λ0
			n = n - 1;
		Output(a, n);
	}
	else
	{
		n = n2;
		for (i = 0; n > i; i++)
		{
			b[i] -= a[i];
			if (b[i] < 0)					//a��Ϊb����
				b[i] += 10, b[i + 1]--;
		}
		printf("-");
		while (b[n - 1] == 0)
			n = n - 1;
		Output(b, n);
	}
 
}
 
void HighMultiply(char x1[], char x2[])
{
	int i, j = 0, n, n1 = strlen(x1), n2 = strlen(x2);
	int a[N] = { 0 }, b[N] = { 0 }, c[1000] = { 0 };
	for (i = n1, j = 1; i >= 1; i--)
		a[j++] = x1[i - 1] - '0';							//�ַ�ת����
	for (i = n2, j = 1; i > 0; i--)
		b[j++] = x2[i - 1] - '0';							//�ַ�ת����
	for (i = 1; n1 >= i; i++)
	{
		for (j = 1; n2 >= j; j++)
		{
			c[i + j - 1] += a[i] * b[j];	//��λ�ˣ�ͬʱ��λ���
			c[i + j] += c[i + j - 1] / 10;
			c[i + j - 1] %= 10;
		}
	}
	n = i + j;
	while (c[n] == 0 && n > 1)
		n--;				//����λ0
	for (i = n; i >= 1; i--)
	{
		printf("%d", c[i]);
	}
}
 
 
void Output(int a[], int n)
{
	int i;
	for (i = n - 1; i >= 0; i--)
		printf("%d", a[i]);
}
int compare(char a[], char b[])
{
	if (strlen(a) > strlen(b))
		return 1;
	if (strlen(a) < strlen(b))
		return 0;
	if (strcmp(a, b) > 0)
		return 1;
	return 0;
}