#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 30

int a, n, m, x;
int res[MAX], shang[MAX];
int main()
{
    cin >> a >> n >> m >> x;
    shang[1] = res[1] = res[2] = a;
    for (int i = 0; i <= INF; i++)
    {
        shang[2] = i;
        for (int sta = 3; sta <= n - 1; sta++)
        {
            shang[sta] = shang[sta - 1] + shang[sta - 2];
            res[sta] = res[sta - 1] + shang[sta] - shang[sta - 1];
        }
        if (res[n - 1] == m)
        {
            printf("%d", res[x]);
            break;
        }
    }
}