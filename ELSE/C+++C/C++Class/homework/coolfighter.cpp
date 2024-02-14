#include <bits/stdc++.h>
using namespace std;
int N, id1, id2, p, dis;

int main()
{
    map<int, int> mp;
    map<int, int>::iterator pos;
    mp[1000000000] = 1;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d%d", &id1, &p);
        pos = mp.lower_bound(p);
        if (pos == mp.end())
            pos--;
        dis = abs(pos->first - p);
        id2 = pos->second;
        if (pos != mp.begin())
        {
            pos--;
            if (abs(pos->first - p) < dis || (abs(pos->first - p) == dis && pos->second < id2))
                id2 = pos->second;
        }
        printf("%d %d\n", id1, id2);
        pos = mp.find(p);
        if (pos == mp.end() || pos->second > id1)
            mp[p] = id1;
    }
}