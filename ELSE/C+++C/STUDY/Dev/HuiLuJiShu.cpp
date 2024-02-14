#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[1<<22][22],g[23][23];

signed main() {
	int n=1<<21;
	for(int i=1; i<=21; i++) for(int j=1; j<=21; j++) if(__gcd(i , j) == 1)
	g[i-1][j-1]=g[j-1][i-1]=1;
	dp[1][0]=1;
	for(int i=1; i<n; i++) {
		for(int j=0; j<21; j++) {
			if(!(i>>(j)&1))continue;
			for(int k=0; k<21; k++) {
				if(!g[j][k]||(i>>(k)&1))continue;
				dp[i+(1<<k)][k]+=dp[i][j];
			}
		}
	}
	int ans=0;
	for(int i=0; i<21; i++) {
		ans+=dp[n-1][i];
	}
	cout<<ans;
}
