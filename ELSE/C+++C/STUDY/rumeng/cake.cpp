#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
#define N 55
int datas[N][N], flag[N][N];
int n, m,  nx, ny;
char dir;
void getdir()
{
    if (dir == 'N')
        nx += 1;
    if (dir == 'S')
        nx -= 1;
    if (dir == 'W')
        ny -= 1;
    if (dir == 'E')
        ny++;
}
int cnts(int x)
{
    if (x & 1)
        return (x + 1) * (x >> 1) + (x >>1 + 1);
    else
        return (x + 1) * (x >> 1);
}
int main()
{
    cin >> n >> m >> ny >> nx;
    getchar();
    for (int k = 1; k <= m; k++)
    {
        dir = getchar();
        getdir();
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == nx && j == ny)
                {
                    datas[i][j] += cnts(flag[i][j]);
                    flag[i][j] = 1;
                }
                else
                {
                    flag[i][j]++;
                }
            }
        }
    }
    for (int i = n; i; i--)
    {
        for (int j = 1; j <= n; j++)
        {
            datas[i][j] += cnts(flag[i][j]);
            printf("%d ", datas[i][j]);
        }
        printf("\n");
    }   
}