#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000

int head[MAX], idx;
struct Node
{
    int to, nex;
} edge[MAX];
void add(int u, int v)
{
    edge[++idx] = Node{v, head[u]};
    head[u] = idx;
}

// 4 6
// A<B
// A<C
// B<C
// C<D
// B<D
// A<B
struct NODE
{
    int item, val;
};
int n, m;
string s;
int have;
int dutt[MAX], dutt_cha[MAX];
bool flag[MAX];

void tupo1()
{
    queue<int> q;
    for (int i = 1; i <= 26; i++)
    {
        if (!dutt[i] && flag[i])
        {
            q.push(i);
            printf("%c", i + 'A' - 1);
        }
    }
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int i = head[now]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            dutt[to]--;
            if (dutt[to] == 0)
            {
                printf("%c", to + 'A' - 1);
                q.push(to);
            }
        }
    }
}
int k;
void tupo()
{
    queue<NODE> q;
    int max_val = 0, sum = 0;
    for (int i = 1; i <= 26; i++)
    {
        if (dutt_cha[i] == 0 && flag[i])
        {
            sum++;
            q.push(NODE{i, 1});
        }
    }
    while (!q.empty())
    {
        int now = q.front().item, val = q.front().val;
        q.pop();
        for (int i = head[now]; i; i = edge[i].nex)
        {
            int to = edge[i].to;
            dutt_cha[to]--;
            if (dutt_cha[to] == 0)
            {
                max_val = max(max_val, val + 1);
                q.push(NODE{to, val + 1});
                sum++;
            }
        }
    }
    if (max_val == n)
    {
        printf("Sorted sequence determined after %d relations: ", k);
        tupo1();
        cout << '.';
        exit(0);
    }
    if (sum != have)
    {
        printf("Inconsistency found after %d relations.", k);
        exit(0);
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> s;
        k = i;
        int a = s[0] - 'A' + 1, b = s[2] - 'A' + 1;
        if (!flag[a])
        {
            have++;
            flag[a] = true;
        }
        if (!flag[b])
        {
            have++;
            flag[b] = true;
        }
        add(a, b);
        dutt[b]++;
        memcpy(dutt_cha, dutt, sizeof(dutt));
        tupo();
    }
    cout << "Sorted sequence cannot be determined.";
}