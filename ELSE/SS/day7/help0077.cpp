#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX_POINT 1001
typedef struct node
{
    ll x, y;
} node;
int n, d;
node Node_list[MAX_POINT];
bool judge_first(node temp)
{
    return pow(temp.x, 2) + pow(temp.y, 2) <= pow(d + 7.5, 2);
}
bool judge_next_jump(node from, node to)
{
    return pow(from.x - to.x, 2) + pow(from.y - to.y, 2) <= pow(d, 2);
}
bool judge_helped(node to)
{
    return (to.x + d >= 50 || to.x - d <= -50 || to.y + d >= 50 || to.y - d <= -50);
}
bool visits[MAX_POINT];
queue<node> q;
void bfs()
{
    while (!q.empty())
    {
        node from = q.front();
        q.pop();
        if (judge_helped(from))
        {
            printf("Yes\n");
            exit(0);
        }
        for (int i = 1; i <= n; i++)
        {
            node to = Node_list[i];
            if (visits[i])
            {
                continue;
            }
            if (judge_next_jump(from, to))
            {

                visits[i] = true;
                q.push(to);
            }
        }
    }
    printf("No\n");
    exit(0);
}

int main()
{
    cin >> n >> d;
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        if (d >= 42.5)
        {
            flag = true;
            continue;
        }
        node temp;
        cin >> temp.x >> temp.y;
        Node_list[i] = temp;
        if (judge_first(temp))
        {
            q.push(temp);
            visits[i] = true;
        }
    }
    if (flag)
    {
        printf("Yes\n");
        return 0;
    }
    bfs();
}