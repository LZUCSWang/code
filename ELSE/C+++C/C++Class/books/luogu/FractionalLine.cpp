#include <bits/stdc++.h>
using namespace std;
typedef struct man
{
    int id;
    int score;
} man;
man all[5005];
bool cmp(man i, man j)
{
    if (i.score == j.score)
        return i.id < j.id;
    return i.score > j.score;
}
int main()
{
    int line = 100;
    int n, m,cnt = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> all[i].id >> all[i].score;
    sort(all, all + n, cmp);
    for (int i = 0; i < int(m * 1.5); i++)
    {
        cnt++;
        line = min(line, all[i].score);
        if (i == int(m * 1.5) - 1)
        {
            while (i + 1 < n && all[i + 1].score == all[i].score)
            {
                i++;
                cnt++;
                line = min(line, all[i].score);
            }
        }
    }
    cout << line << " " << cnt << endl;
    for (int i = 0; i < cnt; i++)
        cout << all[i].id << " " << all[i].score << endl;
}