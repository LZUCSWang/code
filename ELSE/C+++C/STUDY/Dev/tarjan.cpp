#include<bits/stdc++.h>
using namespace std;

#define MAX 10005
int tim;
int s[MAX],top;
struct node {
	int to,nex;
} edge[MAX];
int n,m;
int head[MAX],color[MAX],idx,num[MAX];
int dfn[MAX],low[MAX];
int col;
int de[MAX];
void add(int u,int v){
	edge[++idx].to=v;
	edge[idx].nex=head[u];
	head[u]=idx;
}
void tarjan(int u) {
	dfn[u]=low[u]=++tim;
	s[++top]=u; 
	for(int i=head[u]; i; i=edge[i].nex) {
		int v=edge[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		} else {
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]) {
		color[u]=++col;
		num[col]++;
		while(s[top]!=u) {
			int t=s[top];
			color[t]=col;
			num[col]++;
			top--;
		}
		top--;
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	for(int i=1; i<=n; i++) {
		if(!dfn[i])tarjan(i);
	}
	for(int i=1; i<=n; i++) {
		for(int j=head[i]; j; j=edge[j].nex) {
			if(color[i]!=color[edge[j].to])de[color[i]]++;
		}
	}
	int ans=0,cnt=0;
	for(int i=1; i<=col; i++) {
		if(!de[i]) {
			ans=i;
			cnt++;
		}
	}
	if(cnt==1)printf("%d",num[ans]);
	else printf("0",ans);
	return 0;
}




void tarjan(){
	
} 
int main(){
	
} 
