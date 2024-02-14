#include "stdio.h"
#include "string.h"
#define N 1000//便于后期处理
#include <stdlib.h>
 
 
void csh()
{
    
printf("\t\t\t\t------百位算法--------\n"
 
       "\t\t\t\t|     加法:1         |\n"
       
       "\t\t\t\t|     减法:2         |\n"
       
       "\t\t\t\t|     乘法:3         |\n"
       
        "\t\t\t\t|   程序结束:4       |\n"
        
       "\t\t\t\t|    重新开始:0      |\n"
       
       "\t\t\t\t----------------------      ");
 
}
 
void abc()
//清屏代码 
{
	system("cls");
	//用了cmd命令清理屏幕 
	
	csh();	
	//调用csh函数 
	
}
 
void HighPlus(char x1[], char x2[]);
void HighMinus(char x1[], char x2[]);
void HighMultiply(char x1[], char x2[]);
void Output(int a[], int n);
int compare(char a[], char b[]);
 
 
 
int main()  // main函数开始程序 
{
csh();  //开始屏幕 
  int a,b,sf=1,js;
  //定义值
  //以防错误 
 char x1[N], x2[N];
 
 
 
for(int i=1;i<=1000;i++)
{
	
	
 
 
if(a==4)
{
	break;
	
	//假如为4的话就直接结束程序 
}
 
 
 
//打印算法序号	
printf("\n请输入算法序号:");
 
 
//输入代码，输入序列号 
 
scanf("%d",&a);
// 
 
 
while(1)
{
  
    if(a<=0||a>=5) 
	//判断是否是0到4以内的 
    
    {
    	if(a==0)  
		//假如为0的话就 直接调用清屏函数清理屏幕 
		
    {
    	abc();
    	
  		break;
  		//清理完屏幕之后重新开始下一轮打印输出代码 
	}
	
 
    		
    	
        printf("\n输入错误请重新输入算法名称");
        //提示输入的值不对 
        break;
        //重新下一轮判断 
    }
    
    
   	if(a==4)  
	   //假如为4程序就结束 
	   
	{
		
		break;
		 //重新下一轮判断 
		 
	}
    
 
    
    printf("\n请输入值用空格隔开:\n");
//    gets(x1);//保证读入的数字可以为高精度
//	gets(x2);
scanf("%s %s",&x1,&x2);
   
    
   
switch(a) 
 //判断值 
{
    case 1: 
	HighPlus(x1, x2); 
	 //调用加法函数，成功就结束 
		break;
		
    
    case 2: HighMinus(x1, x2);
	//调用减法函数，成功就结束 
		break;
		
    
    case 3: HighMultiply(x1, x2);
	//调用乘法函数，成功就结束 
		break;
		
 
    default : break;  
	//都不满足就跳出循环 
 }
    
 
printf("\n\n\t\t>>是否继续(1/0)<<:");
//打印判断是否继续？
 
scanf("%d",&sf);
//输出sf的值 
 
 
if(sf==0)  
  //假如他的值为0就跳出循环 
 {
 	
break;
 
 }
    
 
    
} 
 
}
 
printf("\t\t\n""<程序结束>""");
//程序到这里结束！
//goob bai! 
 
return 0;   
 
//程序结束 
}
 
void HighPlus(char x1[], char x2[])
{
	int i, j, n, n1 = strlen(x1), n2 = strlen(x2);
	int a[N] = { 0 }, b[N] = { 0 };
	for (i = n1 - 1, j = 0; i >= 0; i--)
		a[j++] = x1[i] - '0';		//字符转整数
	for (i = n2 - 1, j = 0; i >= 0; i--)
		b[j++] = x2[i] - '0';		//字符转整数
	if (n1 > n2)
		n = n1;
	else						//取高位数
		n = n2;
	for (i = 0; n > i; i++)
	{
		a[i] += b[i];
		a[i + 1] += a[i] / 10;		//按位做加法
		a[i] = a[i] % 10;
	}
	if (a[n] != 0)
		n = n + 1;			//如果最高位进位，位数加一
	Output(a, n);
}
void HighMinus(char x1[], char x2[])
{
	int i, j = 0, n, n1 = strlen(x1), n2 = strlen(x2);
	int a[N] = { 0 }, b[N] = { 0 };
	for (i = n1 - 1, j = 0; i >= 0; i--)
		a[j++] = x1[i] - '0';		//字符转整数
	for (i = n2 - 1, j = 0; i >= 0; i--)
		b[j++] = x2[i] - '0';		//字符转整数
	if (compare(x1, x2) == 1)		//判断谁大谁小
	{
		n = n1;
		for (i = 0; n > i; i++)
		{
			a[i] -= b[i];
			if (a[i] < 0)				//按位做减法
				a[i] += 10, a[i + 1]--;
		}
		while (a[n - 1] == 0)		//去首位0
			n = n - 1;
		Output(a, n);
	}
	else
	{
		n = n2;
		for (i = 0; n > i; i++)
		{
			b[i] -= a[i];
			if (b[i] < 0)					//a换为b即可
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
		a[j++] = x1[i - 1] - '0';							//字符转整数
	for (i = n2, j = 1; i > 0; i--)
		b[j++] = x2[i - 1] - '0';							//字符转整数
	for (i = 1; n1 >= i; i++)
	{
		for (j = 1; n2 >= j; j++)
		{
			c[i + j - 1] += a[i] * b[j];	//按位乘，同时错位相加
			c[i + j] += c[i + j - 1] / 10;
			c[i + j - 1] %= 10;
		}
	}
	n = i + j;
	while (c[n] == 0 && n > 1)
		n--;				//除首位0
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