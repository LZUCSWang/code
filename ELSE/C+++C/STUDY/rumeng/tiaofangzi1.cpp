#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=500000;
const long long neInf=0x8080808080808080;
struct gezi {
    int juli;
    int zhi;
} a[maxn+1];
long long dp[maxn+1];
int q[maxn+1];
int n,d,k,lbound,rbound,ans=-1;
long long sum;

long long dynamic_programming(int zuo, int you) {
    memset(dp,0x80,sizeof(dp));
    dp[0]=0;
    memset(q,0,sizeof(q));
    int tou=1, wei=0, j=0;

    for (int i=1; i<=n; i++) {
        while (a[i].juli-a[j].juli>=zuo&&j<i) {
            if (dp[j]!=neInf) {
                while (tou<=wei&&dp[q[wei]]<=dp[j])
                    wei--;
                q[++wei]=j;
            }
            j++;
        }
        while (tou<=wei&&a[i].juli-a[q[tou]].juli>you)
            tou++;
        if (tou<=wei)
            dp[i]=dp[q[tou]]+a[i].zhi;
    }
    long long num=neInf;
    for (int i=1; i<=n; i++)
        if (dp[i]>num)
            num=dp[i];
    return num;
}

int main() {
    cin>>n>>d>>k;
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i].juli);
        scanf("%d",&a[i].zhi);
        if (a[i].zhi>0)
            sum+=a[i].zhi;
    }
    if (sum<k) {
        cout<<"-1"<<endl;
        return 0;
    }
    rbound=max(a[n].juli,d);
    while (lbound<=rbound) {
        int mid=(lbound+rbound)/2;
        int leftt=max(1,d-mid);
        int rightt=d+mid;
        long long num=dynamic_programming(leftt,rightt);
        if (num<k)
            lbound=mid+1;
        else {
            ans=mid;
            rbound=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}