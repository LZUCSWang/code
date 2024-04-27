#include <bits/stdc++.h>
using namespace std;
#define MAX_N 1005
struct node
{
    int to, nex;
} edges[MAX_N];
int head[MAX_N];
int indexs;
int n;
stack<int> S;
int flag[MAX_N];
void add(int u, int v)
{
    edges[++indexs].to = v;
    edges[indexs].nex = head[u];
    head[u] = indexs;
}
int dutt[MAX_N];
vector<int> vex;
int cnt;
void tubu()
{
    for (int i = 0; i < vex.size(); i++)
    {
        int v = vex[i];
        if (dutt[v] == 0)
        {
            S.push(v);
            cnt++;
        }
    }
    while (!S.empty())
    {
        int u = S.top();
        S.pop();
        for (int i = head[u]; i; i = edges[i].nex)
        {
            int v = edges[i].to;
            dutt[v]--;
            if (dutt[v] == 0)
            {
                dutt[v] = 1;
                S.push(v);
                cnt++;
            }
        }
    }
    if (cnt != vex.size())
    {
        printf("0\n");
    }
    else
    {
        printf("1\n");
    }
    exit(0);
}
int main()
{
    int a, b;
    while (scanf("%d%d", &a, &b) == 2)
    {
        if (a == -1 && b == -1)
            tubu();
        else
        {
            if (flag[a] == 0)
            {
                vex.push_back(a);
                flag[a] = 1;
            }
            if (flag[b] == 0)
            {
                vex.push_back(b);
                flag[b] = 1;
            }
            dutt[b] += 1;
            add(a, b);
        }
    }
}