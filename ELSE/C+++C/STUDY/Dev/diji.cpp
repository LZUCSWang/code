#include<bits/stdc++.h>
using namespace std;
#define MAX 100005
#define INF 2147483647
#define ll long long
int n,m,b;
int idx,head[MAX];
bool vis[MAX];
int dis[MAX];
int f[MAX];
struct Node {
	int to;
	ll dis;
	bool operator<(Node p)const {
		return dis>p.dis;
	}
};
struct point {
	int to,w,nex;
} edge[MAX*10];
void add(int u,int v,int w) {
	edge[++idx].to=v;
	edge[idx].w=w;
	edge[idx].nex=head[u];
	head[u]=idx;
}

bool diji(int minf) {
	if(f[1]>minf)return false;
	for(int i=1; i<=n; i++) {
		dis[i]=INF;//
	}
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	priority_queue<Node> q;
	q.push((Node) {
		1,0
	});
	while(!q.empty()) {
		Node now=q.top();
		q.pop();
		if(vis[now.to])continue;
		if(now.to==n)break;
		int u=now.to;
		vis[u]=true;
		for(int i=head[u]; i; i=edge[i].nex) {
			int to=edge[i].to;
			if(!vis[to]&&f[to]<=minf&&dis[to]>now.dis+edge[i].w) {
				dis[to]=now.dis+edge[i].w;
				q.push((Node) {
					to,dis[to]
				});
			}
		}
	}
	if(dis[n]<=b)return true;
	return false;
}


int main() {
	scanf("%d%d%d",&n,&m,&b);
	for(int i=1; i<=n; i++)
		scanf("%d",f+i);
	while(m--) {
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	if(!diji(INF)) {
		printf("AKF");
		return 0;
	}
	int l=0,r=INF;
	while(l<=r) {
		int mid=(r+l)>>1;
		if(diji(mid))r=mid-1;
		else l=mid+1;
	}
	printf("%d",l);
}
