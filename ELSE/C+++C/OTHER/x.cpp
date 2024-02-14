/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\OTHER\x.cpp
 * @Description: 
 */
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,t;
vector<pair<int, int> > ver;
int main(){
	cin>>t>>n;
	int x,y;
	for(int i=1; i<=n; i++){
		cin>>x>>y;
		ver.push_back(make_pair(x,y));
	}
	sort(ver.begin(), ver.end());
	int now=1,pos=0,ans=0; // now未打扫 
	while(pos<ver.size() && now<=t){
		int mx=0;
		while(pos<ver.size() && ver[pos].first<=now){
			mx = max(mx, ver[pos].second);
			pos++; // pos之前的R都比下一次的now要小,全部舍弃 
		}
		if(mx<=now-1)break; // 无法打扫到新的地方  
		now = mx+1;
		ans++;
	}
	if(now>t)cout<<ans;
	else cout<<-1;
	return 0;
}
