#include <bits/stdc++.h>
using namespace std;// 电话部分
typedef pair<int, int> PII;
struct inf {
    int total_time;
    int times;
    double degree;
    int score, intimacy, lv;
    set<int>may_fri1;
    set<int>may_fri2;
};
double rate(int x) {
    if (x < 16)  return 0.5;
    else if (x < 35) return 0.7;
    else if (x < 68) return 0.8;
    else if (x < 100) return 0.9;
    else return 1;
}
int cal(int x) {
    if (x < 2)  return 0;
    else if (x < 3) return 10;
    else if (x < 5) return 40;
    else if (x < 10) return 80;
    else if (x < 20) return 100;
    else if (x < 30) return 120;
    else if (x < 60) return 150;
    else if (x < 120) return 185;
    else if (x < 180) return 200;
    else if (x < 240) return 215;
    else if (x < 300) return 225;
    else return 230;
}
int level(int x) {
    if (x < 200) return 1;
    else if (x < 500) return 2;
    else if (x < 1000) return 3;
    else if (x < 2000) return 4;
    else if (x < 3000) return 5;
    else if (x < 5000) return 6;
    else if (x < 7000) return 7;
    else if (x < 9000) return 8;
    else if (x < 10000) return 9;
    else return 10;
}
map<PII, inf>h;
int best_friend(int x, int y) {
    int best = 0, pre = 0;
    for (auto &&i : h) {
        if (i.first.first == x && i.first.second != y) {
            best = i.second.intimacy > pre ? i.first.second : best;
            pre = max(pre, i.second.intimacy);
        }
        if (i.first.first != y && i.first.second == x) {
            best = i.second.intimacy > pre ? i.first.first : best;
            pre = max(pre, i.second.intimacy);
        }
    }
    return best;
}
set<int> maybe_friends(int x) {
    int mid = best_friend(x, 0);
    set<int> friends;
    int ans = best_friend(mid, x);
    if (!h.count({ ans,x }) && !h.count({ x,ans }))
        friends.insert(ans);
    mid = best_friend(x, mid);
    ans = best_friend(mid, x);
    if (!h.count({ ans,x }) && !h.count({ x,ans }))
        friends.insert(ans);
    return friends;
}

int main() {
    int n = 5073;
    fstream f;
    f.open("data.txt", ios::in);
    FILE *f1 = fopen("text.txt", "w");
    while (n--) {
        int x, y, z;char ch;
        while ((ch = f.get()) != 'A');
        f >> x;
        while ((ch = f.get()) != 'A');
        f >> y >> z;
        int t = cal(z);
        if (y > x) swap(x, y);
        h[{x, y}].total_time += z;
        h[{x, y}].score += t;
        h[{x, y}].times++;
    }
    for (auto &it : h) {
        auto &fir = it.first;
        auto &sec = it.second;
        sec.degree = rate(sec.times);
        sec.intimacy = sec.degree * sec.score + 0.5;//四舍五入
        sec.lv = level(sec.intimacy);
        sec.may_fri1 = maybe_friends(fir.first);
        sec.may_fri2 = maybe_friends(fir.second);
        int tmp = 0;
        for (auto &i : sec.may_fri2) {
            if (!h.count({ i,fir.first }) && !h.count({ fir.first,i }))
                tmp = i;
        }

        fprintf(f1, "A%03d \t A%03d \t %d \t %d \t %d \t %d\n", fir.first,
            fir.second, sec.total_time, sec.times, sec.intimacy, sec.lv);
        int t = sec.intimacy;
        if (t < 2000) fprintf(f1, "Just acquaintance\n");
        else if (t < 7000) fprintf(f1, "Good relationship(such as friends,colleagues)\n");
        else fprintf(f1, "Close relationships(such as family,bestie)\n");
        if (tmp)
            fprintf(f1, "A%03d maybe know A%03d from A%03d\n", fir.first, tmp, fir.second);
        fprintf(f1, "\n");
    }
    return 0;
}