#include<stdio.h>
int n,c,datas[100000],vis[100000]={0},b[100000],sum=0,flag=0;
void dfs(int s,int step,int cnt);
int main()
{
	scanf("%d%d",&n,&c);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&datas[i]);
		sum+=datas[i];
	}
	if(sum<c)//剪枝这一步非常重要，没有的话会时间超限 
	{
		goto exit;
	}
	dfs(0,0,0);
	exit:
	if(flag==0)printf("No Solution!\n");
	return 0;
}
void dfs(int s,int step,int cnt)
{
	if(s>c||flag==1)return ;
	if(s==c&&flag==0) 
	{
		for(int i=0;i<cnt-1;i++)
		{
			printf("%d ",b[i]);
		}
		printf("%d\n",b[cnt-1]);
		flag=1;
		return ;
	}
	for(int i=step;i<n;i++)
	{
		if(vis[i]==0)
		{
			vis[i]=1;
			b[cnt]=datas[i];
			dfs(s+datas[i],step+1,cnt+1);
			vis[i]=0;
		}
	}
}