#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX_POINT 1001
typedef struct node
{
    ll x, y, z;
    bool flag;
} node;
node Node_list[MAX_POINT];
queue<node> q;
ll N;
ll n, h, r;
void clear(queue<node> &q)
{
    queue<node> empty;
    swap(empty, q);
}
double dis(node a, node b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
void bfs()
{
    while (!q.empty())
    {
        node from = q.front();
        q.pop();
        for (ll i = 1; i <= n; i++)
        {
            node to = Node_list[i];
            if (to.flag)
            {
                continue;
            }
            if (dis(from, to) <= double(r * 2))
            {
                if (to.z + r >= h)
                {
                    printf("Yes\n");
                    return;
                }
                to.flag = true;
                Node_list[i].flag = true;
                q.push(to);
            }
        }
    }
    printf("No\n");
}
void init()
{
    clear(q);
}
void main_work()
{
    cin >> n >> h >> r;
    bool flag = false;
    for (ll i = 1; i <= n; i++)
    {
        node temp;
        scanf("%lld %lld %lld", &temp.x, &temp.y, &temp.z);
        temp.flag = false;
        Node_list[i] = temp;
        if (temp.z - r <= 0)
        {
            // printf("Yes\n");
            if (temp.z + r >= h)
            {
                flag = true;
            }
            Node_list[i].flag = true;
            temp.flag = true;
            q.push(temp);
        }
    }
    if (flag)
    {
        printf("Yes\n");
        return;
    }
    bfs();
}
int main()
{
    cin >> N;
    for (ll i = 1; i <= N; i++)
    {
        init();
        main_work();
    }
    return 0;
}