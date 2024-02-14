#include<bits/stdc++.h>
using namespace std;
#define MAX 10005
int al,ar,ml,mr,ql,qr;
int tree[MAX],datas[MAX];
int alazy[MAX],mlazy[MAX];
int num;
int n,m,p;
void build(int pos,int l,int r) {
	mlazy[pos]=1;
	if(l==r) {
		tree[pos]=datas[l];
		return;
	}
	int mid=(l+r)>>1;
	build(pos<<1,l,mid);
	build(pos<<1|1,mid+1,r);
	tree[pos]=(tree[pos<<1]+tree[pos<<1|1])%p;
}
void pushDown(int pos,int l,int r) {
	int mid=(l+r)>>1;

	tree[pos<<1]=(tree[pos<<1]*mlazy[pos]+alazy[pos]*(l-mid+1))%p;
	tree[pos<<1|1]=(tree[pos<<1|1]*mlazy[pos]+alazy[pos]*(r-mid))%p;

	mlazy[pos<<1]=(mlazy[pos<<1]*mlazy[pos])%p;
	mlazy[pos<<1|1]=(mlazy[pos<<1|1]*mlazy[pos])%p;

	alazy[pos<<1]=(alazy[pos]+alazy[pos<<1]*mlazy[pos])%p;
	alazy[pos<<1|1]=(alazy[pos]+alazy[pos<<1|1]*mlazy[pos])%p;

	alazy[pos]=0,mlazy[pos]=1;
}
void add(int pos,int l,int r) {
	if(l>=al&&r<=ar) {
		alazy[pos]=alazy[pos]+num;
		tree[pos]=tree[pos]+num*(r-l+1);
		return;
	}
	pushDown(pos,l,r);
	int mid=(l+r)>>1;
	if(al<=mid)add(pos<<1,l,mid);
	if(ar>mid)add(pos<<1|1,mid+1,r);
	tree[pos]=tree[pos<<1]+tree[pos<<1|1];
}
void mul(int pos,int l,int r) {
	if(l>=ml&&r<=mr) {
		alazy[pos]=alazy[pos]*num;
		mlazy[pos]=mlazy[pos]*num;
		tree[pos]=tree[pos]*num;
		return;
	}
	pushDown(pos,l,r);
	int mid=(l+r)>>1;
	if(ml<=mid)mul(pos<<1,l,mid);
	if(mr>mid)mul(pos<<1|1,mid+1,r);
	tree[pos]=tree[pos<<1]+tree[pos<<1|1];
}
int query(int pos,int l,int r) {
	int ans=0;
	if(l>=ql&&r<=qr) {
		return tree[pos];
	}
	pushDown(pos,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid)ans+=query(pos<<1,l,mid);
	if(qr>mid)ans+=query(pos<<1|1,mid+1,r);
	return ans;
}
int main() {
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1; i<=n; i++) {
		scanf("%d",datas+i);
	}
	build(1,1,n);
	while(m--) {
		int cho,a,b;
		scanf("%d",&cho);
		if(cho==2) {
			scanf("%d%d%d",&al,&ar,&num);
			add(1,1,n);
		} else if(cho==1) {
			scanf("%d%d%d",&ml,&mr,&num);
			mul(1,1,n);
		} else if(cho==3) {
			scanf("%d%d",&ql,&qr);
			printf("%d\n",query(1,1,n)%p);
		}
	}
	return 0;
}
