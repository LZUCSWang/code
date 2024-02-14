#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool v[25][25]; 
ll dp[1<<21][25];
inline int gcd(int datas, int b){
	return b==0 ? datas : gcd(b, datas%b);
}
int main(void)
{
	ll res = 0;
	//存边,注意下标 
	for(int i = 1;i <= 21; i++){
		for(int j = 1; j <= 21; j++){
		if(gcd(i, j) == 1) 
			v[i-1][j-1] = v[j-1][i-1] = true;
		else
			v[i-1][j-1] = v[j-1][i-1] = false;
	}
	}
	dp[1][0] = 1;
	for(int i = 1; i < (1<<21); i++){
	for(int j = 0; j < 21; j++){
		
		//如果当前状态中不存在楼j，跳过 
		if(!(i>>j&1)) continue;
		            
		//寻找从楼j能够到达的下一栋楼
		for(int k = 0; k < 21; k++){
			
			//楼k已经访问或者j到k无边，跳过 
			if((i>>k&1) || !v[j][k]) continue;
			
			dp[i+(1<<k)][k] += dp[i][j];
		}
	}
	}
	
	//将以i为结尾点的回路求和 
	for(int i = 0; i < 21; i++) 
		res += dp[(1<<21)-1][i];
	cout <<res;
	return 0;
} 