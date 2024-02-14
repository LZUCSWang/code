#include <bits/stdc++.h>
using namespace std;
#define MAX 1000000
#define INF 2147483647
int n, m, q;
struct node
{
    int to, inx;
} edges[MAX];          // 边集
int indexs, head[MAX]; // 链式前向星
typedef struct Node
{
    int to, dis;
    bool operator<(Node p) const // 重载小于号
    {
        return dis > p.dis;
    }
} Node;
void add(int from, int to)
{
    edges[++indexs].to = to;
    edges[indexs].inx = head[from];
    head[from] = indexs;
}
void input()
{
    cin >> n >> m >> q;
    for (int i = 1, a, b; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
}
int dis_ji[MAX], dis_ou[MAX];
void diji()
{
    priority_queue<Node> q;
    memset(dis_ji, 0x3f3f3f, sizeof(dis_ji));
    memset(dis_ou, 0x3f3f3f, sizeof(dis_ou));
    q.push(Node{1, 0});
    dis_ou[1] = 0;
    while (!q.empty())
    {
        Node temp = q.top();
        q.pop();
        for (int i = head[temp.to]; i; i = edges[i].inx)
        {
            int to = edges[i].to;
            if (temp.dis & 1)
            {
                if (temp.dis + 1 < dis_ou[to])
                {
                    dis_ou[to] = temp.dis + 1;
                    q.push(Node{to, dis_ou[to]});
                }
            }
            else
            {
                if (temp.dis + 1 < dis_ji[to])
                {
                    dis_ji[to] = temp.dis + 1;
                    q.push(Node{to, dis_ji[to]});
                }
            }
        }
    }
}
int main()
{
    input();
    diji();
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (y & 1)
            if (dis_ji[x] > y)
                printf("No\n");
            else
                printf("Yes\n");
        else if (dis_ou[x] > y)
            printf("No\n");
        else
            printf("Yes\n");
    }
}