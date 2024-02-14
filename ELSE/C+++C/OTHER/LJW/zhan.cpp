#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

//顺序栈定义
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 5 //顺序栈存储空间的初始分配量
typedef int Status;
typedef int SElemType;

typedef struct
{
	SElemType *base; //栈底指针
	SElemType *top;	 //栈顶指针
	int stacksize;	 //栈可用的最大容量
} SqStack;

//算法3.1　顺序栈的初始化
Status InitStack(SqStack &s)
{
	//构造一个空栈S
	s.base = new SElemType[MAXSIZE]; //为顺序栈动态分配一个最大容量为MAXSIZE的数组空间
	if (!s.base)
		exit(OVERFLOW);	   //存储分配失败
	s.top = s.base;		   // top初始为base，空栈
	s.stacksize = MAXSIZE; // stacksize置为栈的最大容量MAXSIZE
	return OK;
}

void DestroyStack(SqStack &s)
{
	/* 销毁栈S，S不再存在 */
	delete[] s.base;
	s.base = s.top = NULL;
	s.stacksize = 0;
}

//算法3.2　顺序栈的入栈
Status Push(SqStack &s, SElemType e)
{
	/****在此下面完成代码***************/
	if (s.top - s.base == MAXSIZE)
		return ERROR;
	*s.top = e;
	s.top++;
	return OK;
	/***********************************/
}

//算法3.3　顺序栈的出栈
Status Pop(SqStack &s, SElemType &e)
{
	/****在此下面完成代码***************/
	if (s.base == s.top)
		return ERROR;
	s.top--;
	e = *s.top;
	return OK;

	/***********************************/
}

//算法3.4　取顺序栈的栈顶元素
SElemType GetTop(SqStack s) //返回S的栈顶元素，不修改栈顶指针
{
	/****在此下面完成代码***************/
	if (!s.base)
		return ERROR;
	return *(s.top - 1);

	/***********************************/
}

bool StackEmpty(SqStack S)
{
	/****在此下面完成代码***************/
	if (S.top == S.base)
		return true;
	else
		return false;

	/***********************************/
}
Status operator_s(int e1, char ch, int e2)
{
	switch (ch)
	{
	case '+':
		return e1 + e2;
		break;
	case '-':
		return e1 - e2;
		break;
	case '*':
		return e1 * e2;
		break;
	case '/':
		return e1 / e2;
		break;
	}
	return 0;
}
int main()
{
	SqStack s;
	InitStack(s);
	char ch;
	int e1, e2, n, temp = 0, i = 0;
	char str[10000];
	gets(str);
	// printf("%s\n",str);
	while (str[i] != '@')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			temp = temp * 10 + str[i] - '0';
			if (str[i + 1] == ' ')
			{
				Push(s, temp);
				n=GetTop(s);
				// printf("%d\n",n);
				// return 0;
				temp = 0;
			}
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			ch = str[i];
			Pop(s, e2);
			Pop(s, e1);
			n = operator_s(e1, ch, e2);
			// printf("%d\n",n);
			// return 0;
			Push(s, n);
		}
		i++;
	}
	cout << *(s.top - 1);
	return 0;
}
