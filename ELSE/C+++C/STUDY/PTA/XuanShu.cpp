#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000005
typedef long long ll;
bool isPrime[MAXN];
int n, k;
int xx[25];

int nowSum, ans;
// void getPrime(int x)
// {
//     for (int i = 2; i <= x; i++)
//     {
//         isPrime[i] = true;
//     }
//     for (int i = 2; i <= x; i++)
//     {
//         if (isPrime[i])
//         {
//             for (int j = i; i * j <= x; j++)
//                 isPrime[i * j] = false;
//         }
//     }
// }
int prime[MAXN];
int c = 0;
bool isVisit[MAXN]; // 默认都是false
void EulerSevie(int n)
{
    for (int i = 2; i <= n; ++i) // 老规矩，遍历区间
    {
        if (isVisit[i] == false) // 如果这个数未被访问，则是素数
            prime[++c] = i;      // 将素数保存在素数数组里面，计数+1
        // 下面for循环及里面的语句才是这个算法的精髓，我们下面细讲
        for (int j = 1; j <= c && i * prime[j] <= n; ++j)
        {
            isVisit[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}

void dfs(int nowIndex, int hadNum)
{
    if (hadNum == k)
    {
        if (!isVisit[nowSum])
            ans++;
    }
    for (int i = nowIndex; i <= n; i++)
    {
        nowSum += xx[i];
        dfs(i + 1, hadNum + 1);
        nowSum -= xx[i];
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> xx[i];
    }
    EulerSevie(100000000);
    dfs(1, 0);
    cout << ans << endl;
}