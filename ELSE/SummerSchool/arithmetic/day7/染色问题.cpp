#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX 5000005
#define MAX_POINT 505
int graph[MAX_POINT][MAX_POINT], colors[MAX_POINT];
// 6 8 3
// 2 1
// 1 3
// 4 6
// 2 5
// 2 4
// 5 4
// 5 6
// 3 6
// 4
// 1 2 3 3 1 2
// 4 5 6 6 4 5
// 1 2 3 4 5 6
// 2 3 4 2 3 4
int n, m, k, color_cnt, color_happen[MAX];
void input()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
        graph[b][a] = 1;
    }
}

void judge_all()
{
    int nn;
    cin >> nn;
    for (int i = 1; i <= nn; i++) //所有测试样例
    {
        memset(color_happen, 0, sizeof(color_happen));
        memset(colors, 0, sizeof(colors));
        color_cnt = 0;
        for (int j = 1; j <= n; j++)
        { //每个测试样例的输入
            cin >> colors[j];
            if (color_happen[colors[j]] == 0)
            {
                color_happen[colors[j]] = 1;
                color_cnt++;
            }
        }
        if (color_cnt != k)
        {
            cout << "No" << endl;
            continue;
        }
        bool flag = false;
        for (int i = 1; i < n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                if (graph[i][j] == 1)
                {
                    if (colors[i] == colors[j])
                    {
                        cout << "No" << endl;
                        flag = true;
                        break;
                    }
                }
            }
            if (flag)
            {
                break;
            }
        }
        if (!flag)
        {
            cout << "Yes" << endl;
        }
    }
}
int main()
{
    input();
    judge_all();
    return 0;
}