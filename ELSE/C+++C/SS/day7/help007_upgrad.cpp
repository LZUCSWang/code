#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX_POINT 30
typedef struct node
{
    ll x, y, dis;
} node;
bool cmp(node a, node b)
{
    return a.dis < b.dis;
}
int n, d;
#define pair_node pair<int, int>
node Node_list[MAX_POINT];
bool judge_first(int temp)
{
    return pow(Node_list[temp].x, 2) + pow(Node_list[temp].y, 2) <= pow(d + 7.5, 2);
}
bool judge_next_jump(int from, int to)
{
    return pow(Node_list[from].x - Node_list[to].x, 2) + pow(Node_list[from].y - Node_list[to].y, 2) <= pow(d, 2);
}
bool judge_helped(int to)
{
    return (Node_list[to].x + d >= 50 || Node_list[to].x - d <= -50 || Node_list[to].y + d >= 50 || Node_list[to].y - d <= -50);
}
int father[MAX_POINT];
bool visits[MAX_POINT];
queue<pair_node> q;
stack<pair<int, int>> s;
void print_father(int start)
{
    s.push(make_pair(Node_list[start].x, Node_list[start].y));
    int fa = father[start];
    while (fa != -1)
    {
        s.push(make_pair(Node_list[fa].x, Node_list[fa].y));
        fa = father[fa];
    }
    while (!s.empty())
    {
        pair<int, int> temp = s.top();
        s.pop();
        printf("%d %d\n", temp.first, temp.second);
    }
}
void bfs()
{
    while (!q.empty())
    {
        pair_node from_node = q.front();
        q.pop();
        if (judge_helped(from_node.first))
        {
            printf("%d\n", from_node.second + 1);
            print_father(from_node.first);
            exit(0);
        }
        for (int i = 1; i <= n; i++)
        {
            node to = Node_list[i];
            if (visits[i])
            {
                continue;
            }
            if (judge_next_jump(from_node.first, i))
            {
                visits[i] = true;
                q.push({i, from_node.second + 1});
                father[i] = from_node.first;
            }
        }
    }
    printf("0\n");
    exit(0);
}

int main()
{
    cin >> n >> d;
    memset(father, -1, sizeof(father));
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        cin >> Node_list[i].x >> Node_list[i].y;
        Node_list[i].dis = pow(Node_list[i].x, 2) + pow(Node_list[i].y, 2);
        if (d >= 42.5)
        {
            flag = true;
            continue;
        }
    }
    if (flag)
    {
        printf("1\n");
        return 0;
    }
    sort(Node_list + 1, Node_list + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        if (judge_first(i))
        {
            q.push({i, 1});
            visits[i] = true;
        }
    bfs();
}