#include <bits/stdc++.h>
using namespace std;
typedef struct
{
    int id;
    int power;
    int score;
} player;
player all[99999];
bool cmp(player i, player j)
{
    if (i.score == j.score)
        return i.id < j.id;
    return i.score > j.score;
}
int main()
{
    int n, r, q;
    cin >> n >> r >> q;
    for (int i = 0; i < 2 * n; i++)
    {
        all[i].id = i + 1;
        cin >> all[i].score;
    }
    for (int i = 0; i < 2 * n; i++)
        cin >> all[i].power;
    sort(all, all + 2 * n, cmp);
    // for (int i = 0; i < 2 * n; i++)
    //     cout << all[i].id << " " << all[i].score << " " << all[i].power << endl;
    for (int i = 0; i < r; i++) //进行r轮比赛
    {
        for (int battle = 0; battle < 2*n-1; battle += 2)
            (all[battle].power > all[battle + 1].power) ? all[battle].score++ : all[battle + 1].score++;
        sort(all, all + 2 * n, cmp);
    }
    cout << all[q - 1].id << endl;
}
