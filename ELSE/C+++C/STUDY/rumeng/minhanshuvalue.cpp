#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10005
int n, m;
int f[MAX][3];
//小根堆
priority_queue<int, vector<int>, greater<int>> q;
int place[MAX];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &f[i][0], &f[i][1], &f[i][2]);
        q.push(f[i][0] + f[i][1] + f[i][2]);
    }
    for (int i = 1; i <= n; i++)
        place[i] = 2;
    for (int i = 1; i <= m; i++)
    {
        printf("%d ", q.top());
        q.pop();
        int minn = INF, idx = 0;
        for (int j = 1; j <= n; j++)
        {
            int temp = f[j][0] * place[j] * place[j] + f[j][1] * place[j] + f[j][2];
            if (temp < minn)
                minn = temp, idx = j;
        }
        q.push(minn);
        place[idx]++;
    }
}