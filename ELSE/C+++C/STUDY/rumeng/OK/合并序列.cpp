#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
// 3
// 2 6 6
// 1 4 8
struct Node
{
    int sum, idx;
    bool operator<(const Node &a) const
    {
        return sum > a.sum;
    }
};
priority_queue<Node> q;
int n, a[MAX], b[MAX], idx[MAX], place[MAX];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", b + i);
        q.push(Node{b[1] + a[i], i});
        idx[b[1] + a[i]] = i;
    }
    for (int i = 1, j; i <= n; i++)
    {
        printf("%d ", q.top().sum);
        j = q.top().idx;
        q.pop();
        place[j]++;
        q.push(Node{a[j] + b[place[j] + 1], j});
    }
}