#include <bits/stdc++.h>
using namespace std;
typedef struct
{
    char name[20];
    int score;
    int classscore;
    char gan;
    char xi;
    int lun;
} stu;
int main()
{
    int n = 0, cnt = 0, most = 0, sum = 0;
    cin >> n;
    stu one, cnt;
    for (int i = 0; i < n; i++)
    {
        cin >> one.name >> one.score >> one.classscore >> one.gan >> one.xi >> one.lun;
        cnt = 0;
        if (one.score > 80 && one.lun > 0)
            cnt += 8000;
        if (one.score > 85 && one.classscore > 80)
            cnt += 4000;
        if (one.score > 90)
            cnt += 2000;
        if (one.score > 85 && one.xi == 'Y')
            cnt += 1000;
        if (one.classscore > 80 && one.gan == 'Y')
            cnt += 850;
        if (cnt > most)
        {
            most = cnt;
            cnt = one;
        }
        sum += cnt;
    }
    cout << cnt.name << endl
         << most << endl
         << sum << endl;
}