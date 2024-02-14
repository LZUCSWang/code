#include<bits/stdc++.h>
using namespace std;
int n,t,dp,ans=-0x3f3f3f3f;
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		scanf("%d",&t);
		if(dp>0)
			dp=dp+t;
		else
			dp=t;
		ans=max(dp,ans);
	}
	cout<<ans;
}
