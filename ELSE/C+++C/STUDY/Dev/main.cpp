#include<bits/stdc++.h>
using namespace std;
#define MAX 10005
int n,m,s;
int idx,head[MAX];
int fa[MAX][MAX],depth[MAX],log_[MAX];
struct Node {
	int to,nex;
} edge[MAX];
void add(int u,int v) {
	edge[++idx].to=v;
	edge[idx].nex=head[u];
	head[u]=idx;
}

void dfs(int now,int father) {
	fa[now][0]=father;
	depth[now]=depth[father]+1;
	for(int i=1; i<=log_[depth[now]]; i++) {
		fa[now][i]=fa[fa[now][i-1]][i-1];
	}
	for(int i=head[now]; i; i=edge[i].nex) {
		int to=edge[i].to;
		if(to!=father) {
			dfs(to,now);
		}
	}
}

int LCA(int a,int b) {
	if(depth[a]<depth[b])swap(a,b);
	while(depth[a]>depth[b]) {
		a=fa[a][log_[depth[a]-depth[b]]-1];
	}
	if(a==b)return a;
	for(int i=log_[depth[a]]-1; i>=0; i--) {
		if(fa[a][i]!=fa[b][i]) {
			a=fa[a][i];
			b=fa[b][i];
		}
	}
	return fa[a][0];
}
void init_log() {
	for(int i=1; i<=n; i++) {
		log_[i]=log_[i-1]+((1<<log_[i-1])==i);
	}
}
int main() {
	scanf("%d%d%d",&n,&m,&s);
	init_log();
	for(int i=1; i<=n-1; i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(s,0);
	for(int i=1; i<=m; i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",LCA(a,b));
	}
	return 0;
}

