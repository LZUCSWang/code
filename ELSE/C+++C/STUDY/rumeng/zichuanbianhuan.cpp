// abcd xyz
// abc xu
// ud y
// y yz
#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000
#define ll long long

map<string, int> mp;
struct Node
{
    string s;
    int step;
};
queue<Node> q;
int cnt, step, nexts[MAX], len_b, len_a;
string oring[MAX], too[MAX];
string A, B, now;
char a[MAX], b[MAX];
void getnext()
{
    int j = 0;
    memset(nexts, 0, sizeof(nexts));
    len_b = strlen(b + 1);
    for (int i = 2; i <= len_b; i++)
    {
        while (j && b[j + 1] != b[i])
            j = nexts[j];
        if (b[j + 1] == b[i])
            j++;
        nexts[i] = j;
    }
}
void KMP(int place)
{
    int j = 0;
    len_a = strlen(a + 1);
    for (int i = 1; i <= len_a; i++)
    {
        while (j && a[i] != b[j + 1])
            j = nexts[j];
        if (a[i] == b[j + 1])
            j++;
        if (j == len_b)
        {
            string temp = now.substr(0, i - j) + too[place] + now.substr(i);
            j = nexts[j];
            if (mp[temp] == 0)
            {
                mp[temp] = 1;
                q.push({temp, step + 1});
            }
        }
    }
}

void bfs()
{
    q.push(Node{A, 0});
    while (!q.empty())
    {
        now = q.front().s;
        step = q.front().step;
        q.pop();
        if (now == B)
        {
            cout << step << endl;
            return;
        }
        if (step == 10)
            continue;
        for (int i = 1; i <= cnt; i++)
        {
            strcpy(a + 1, now.c_str());
            strcpy(b + 1, oring[i].c_str());
            getnext();
            KMP(i);
        }
    }
    cout << "NO ANSWER!" << endl;
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> A >> B;
    string temp;
    a[0] = b[0] = 1;
    cnt = 1;
    while (cin >> oring[cnt] >> too[cnt])
        cnt++;
    bfs();
}
