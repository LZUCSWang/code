#include <bits/stdc++.h>
using namespace std;
map<string, int> MAP;
int n, m;
string t;
void input()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t;
        MAP[t] = 1;
    }
}
void main_work()
{
    cin >> m;
    while (m--)
    {
        cin >> t;
        if (MAP[t] == 1)
        {
            printf("OK\n");
            MAP[t] = -1;
        }
        else if (MAP[t] == -1)
        {
            printf("REPEAT\n");
        }
        else
        {
            printf("WRONG\n");
        }
    }
}
int main()
{
    input();
    main_work();
}