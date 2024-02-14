#include <bits/stdc++.h>
using namespace std;
int dp[205][10];
int main()
{
    int n,k;
    cin>>n>>k;
    memset(dp,0,sizeof(dp));
    for (int i=1;i<=n;i++){
        dp[i][1]=dp[i][0]=1;
    }
    for (int j=2;j<=k;j++){
        dp[1][j]=dp[0][j]=0;
    }
    for (int i=2;i<=n;i++){
        for (int j=2;j<=k;j++){
            dp[i][j]=dp[i-1][j-1];
            if (i>=j){
                dp[i][j]+=dp[i-j][j];
            }
        }
    }
    // for (int i=1;i<=n;i++){
    //     for (int j=1;j<=k;j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    cout<<dp[n][k];
}