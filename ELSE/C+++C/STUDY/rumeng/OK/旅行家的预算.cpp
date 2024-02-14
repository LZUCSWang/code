#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
// https://www.luogu.com.cn/problem/P1016
double D1, C, D2, P;
int n;
double dis[MAX], val[MAX];
double full_dis;
void deal(int now, double res_oil, double have_dis, double money)
{
    double res_dis = res_oil * D2;
    if (res_dis + have_dis >= D1)
    {
        printf("%.2f", money);
        exit(0);
    }
    if (now == n && full_dis + have_dis < D1 || now != n && full_dis + have_dis < dis[now + 1])
    {
        printf("No Solution");
        exit(0);
    }
    if (now == n && full_dis + have_dis >= D1)
    {
        double need_oil = (D1 - have_dis) / D2;
        if (res_oil > need_oil)
        {
            printf("%.2f", money);
        }
        else
        {
            printf("%.2f", money + (need_oil - res_oil) * val[now]);
        }
        exit(0);
    }

    int min_idx = 0;
    double temp_min_val = INF;
    for (int i = now + 1; i <= n && dis[i] - have_dis <= full_dis; i++)
    {
        if (val[i] < temp_min_val)
        {
            temp_min_val = val[i];
            min_idx = i;
        }
        if (val[i] < val[now])
        {
            double need_oil = (dis[i] - have_dis) / D2;
            if (res_oil <= need_oil)
            {
                double need_money = (need_oil - res_oil) * val[now];
                money += need_money;
                res_oil = 0;
            }
            else
            {
                res_oil -= need_oil;
            }
            deal(i, res_oil, dis[i], money);
            return;
        }
    }
    if (now <= min_idx)
    {
        //油加满到idx
        if (full_dis + have_dis >= D1)
        {
            double need_oil = (D1 - have_dis) / D2;
            if (res_oil <= need_oil)
            {
                double need_money = (need_oil - res_oil) * val[now];
                money += need_money;
                res_oil = 0;
            }
            else
            {
                res_oil -= need_oil;
            }
            printf("%.2f", money);
            exit(0);
        }
        double need_oil = (C - res_oil);
        double need_money = need_oil * val[now];
        money += need_money;
        deal(min_idx, C - (dis[min_idx] - have_dis) / D2, dis[min_idx], money);
    }
}
// 275.6 11.9 27.4 2.8 2
// 102.0 2.9
// 220.0 2.2
int main()
{
    cin >> D1 >> C >> D2 >> val[0] >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%lf", dis + i, val + i);
    }
    full_dis = C * D2;
    deal(0, 0, 0, 0);
}