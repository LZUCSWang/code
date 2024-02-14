#include <bits/stdc++.h>
using namespace std;
#define node pair<int, int>
queue<pair<node, int>> q;
int ex, ey, sx, sy;
node t1, t2;
node split(string s)
{
    int x, y;
    x = s[0] - 'a' + 1;
    y = s[1] - '1' + 1;
    return make_pair(x, y);
}
map<node, node> MAP;
int seen[9][9];
map<node, string> PATH;
void init_path()
{
    PATH[{-1, -1}] = "LD";
    PATH[{-1, 1}] = "LU";
    PATH[{1, -1}] = "RD";
    PATH[{1, 1}] = "RU";
    PATH[{1, 0}] = "R";
    PATH[{0, 1}] = "U";
    PATH[{-1, 0}] = "L";
    PATH[{0, -1}] = "D";
}
stack<string> path;
void get_path()
{
    init_path();
    while (t2 != t1)
    {
        path.push(PATH[MAP[t2]]);
        node temp;
        temp.first = t2.first - MAP[t2].first;
        temp.second = t2.second - MAP[t2].second;
        t2 = temp;
    }
    while (!path.empty())
    {
        cout << path.top() << endl;
        path.pop();
    }
}
void bfs(node start)
{

    q.push(make_pair(start, 0));
    while (!q.empty())
    {
        pair<node, int> temp = q.front();
        q.pop();
        int x = temp.first.first, y = temp.first.second;
        if (x == ex && y == ey)
        {
            cout << temp.second << endl;
            get_path();
            return;
        }
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx == 0 && dy == 0)
                {
                    continue;
                }
                int nx = x + dx, ny = y + dy;
                if (nx >= 1 && nx <= 8 && ny >= 1 && ny <= 8 && !seen[nx][ny])
                {
                    seen[nx][ny] = 1;
                    q.push({{nx, ny}, temp.second + 1});
                    MAP[{nx, ny}] = {dx, dy};
                }
            }
        }
    }
}
int main()
{
    string s;
    cin >> s;
    t1 = split(s);
    sx = t1.first, sy = t1.second;
    cin >> s;
    t2 = split(s);
    ex = t2.first, ey = t2.second;
    bfs(t1);
}
