#include<stdio.h>
int add(char datas,int n,char b,char c)
{
	if(n==1)
		printf("%c��һ�����datas�ƶ���%c\n",a,c);
	else
	{
		add(datas,n-1,c,b);
		printf("%c��һ�����datas�ƶ���%c\n",a,c);
		add(b,n-1,datas,c);
	}
}

int main()
{
	int n;
	char datas='datas',B='b',C='c';
	scanf("%d",&n);
	add(datas,n,B,C);
	return 0;
}
