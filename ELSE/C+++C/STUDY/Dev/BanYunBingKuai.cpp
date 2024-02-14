#include<bits/stdc++.h>
using namespace std;
#define MAX 100050
int cost,n;
struct node {
	int t,s;
	bool operator<(const node&n)const {
		return t*n.s<s*n.t;
	}
} bing[MAX];
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		scanf("%d%d",&bing[i].t,&bing[i].s);
	}
	sort(bing+1,bing+n+1);
	int t=0;
	for(int i=1; i<=n; i++) {
		cost+=bing[i].s*t;
		t+=bing[i].t;
	}
	cout<<cost;
}
