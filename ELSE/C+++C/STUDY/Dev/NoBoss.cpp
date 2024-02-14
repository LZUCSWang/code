#include<bits/stdc++.h>
using namespace std;
#define MAX 100005
int dp[MAX][2],hap[MAX],n;
bool low[MAX];
vector<int>emp[MAX];

void dfs(int now){
	dp[now][1]=hap[now];
	dp[now][0]=0;
	for(int i=0;i<emp[now].size();i++){
		int to=emp[now][i];
		dfs(to);
		dp[now][0]+=max(dp[to][0],dp[to][1]);
		dp[now][1]+=dp[to][0];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",hap+i);
	}
	for(int i=1;i<=n-1;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		emp[b].push_back(a);
		low[a]=true;
	}
	int root;
	for(int i=1;i<=n;i++){
		if(!low[i]){
			root=i;
			break;
		}
	}
	dfs(root);
	printf("%d",max(dp[root][0],dp[root][1]));
}
