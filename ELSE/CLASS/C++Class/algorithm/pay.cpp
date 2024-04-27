#include <bits/stdc++.h>
using namespace std;
// 支付部分
struct info {
    double profit, send, recv;
    double ave1, ave2, rate, k;
    int t1, t2, lv;
    double Economic;
};

map <string, info>h;
void evaluate(string x, FILE *f1) {
    if (h[x].lv == -3) {
        fprintf(f1, "Particularly poor\n");
    } else if (h[x].lv == -2) {
        fprintf(f1, "Generally poor\n");
    } else if (h[x].lv == -1) {
        fprintf(f1, "Slightly poor\n");
    } else if (h[x].lv == 0) {
        fprintf(f1, "Balance of income and expenditure\n");
    } else if (h[x].lv == 1) {
        fprintf(f1, "Just so-so\n");
    } else if (h[x].lv == 2) {
        fprintf(f1, "well-off\n");
    } else if (h[x].lv == 3) {
        fprintf(f1, "Relatively rich\n");
    } else if (h[x].lv == 4) {
        fprintf(f1, "Generally rich\n");
    } else if (h[x].lv == 5) {
        fprintf(f1, "Very rich\n");
    } else {
        fprintf(f1, "Specially rich\n");
    }
    fprintf(f1, "\n");
}
int level(string x) {
    double c, d;

    if (h[x].rate < 0.25) c = 0.95;
    else if (h[x].rate < 0.45) c = 0.97;
    else if (h[x].rate < 0.55) c = 1;
    else if (h[x].rate < 0.65) c = 1.02;
    else if (h[x].rate < 0.75) c = 1.05;
    else if (h[x].rate < 0.9) c = 1.08;
    else c = 1.1;

    if (h[x].k < 0.25) d = 0.95;
    else if (h[x].k < 0.5)d = 0.97;
    else if (h[x].k < 0.65)d = 1;
    else if (h[x].k < 0.85)d = 1.05;
    else d = 1.1;

    h[x].Economic = c * d * h[x].ave1;

    if (h[x].Economic == 0) {
        if (h[x].ave2 < 1000) {
            return -1;
        } else if (h[x].ave2 < 2000) {
            return -2;
        } else {
            return -3;
        }
    } else {
        if (h[x].Economic < 1000) {
            return 0;
        } else if (h[x].Economic < 2000) {
            return 1;
        } else if (h[x].Economic < 3500) {
            return 2;
        } else if (h[x].Economic < 5000) {
            return 3;
        } else if (h[x].Economic < 7500) {
            return 4;
        } else if (h[x].Economic < 10000) {
            return 5;
        } else return 6;

    }

}
int main() {
    fstream f;
    f.open("input.txt", ios::in);
    FILE *f1 = fopen("output.txt", "w");
    int n = 2243;
    while (n--) {
        string x, y;
        double z;
        f >> x >> y >> z;
        h[x].recv += z;
        h[y].send += z;
        h[x].t1++;
        h[y].t2++;
    }

    for (auto &it : h) {
        auto &fir = it.first;
        auto &sec = it.second;
        if (sec.t1 + sec.t2 >= 6) {
            sec.ave1 = sec.t1 ? sec.recv / sec.t1 : 0;
            sec.ave2 = sec.t2 ? sec.send / sec.t2 : 0;

            sec.profit = sec.recv - sec.send;
            sec.k = (double)sec.t1 / (sec.t2 + sec.t1);
            sec.rate = sec.recv / (sec.send + sec.recv);
            sec.lv = level(fir);

            fprintf(f1, "%s\n  %10.2lf %5d %10.2lf\n",
                fir.c_str(), sec.recv, sec.t1, sec.ave1);
            fprintf(f1, "  %10.2lf %5d %10.2lf\n",
                sec.send, sec.t2, sec.ave2);

            fprintf(f1, "  %10.2lf %5.2lf %10.2lf %10.2lf \n",
                sec.profit, sec.rate, sec.k, sec.Economic);

            evaluate(fir, f1);
        }
    }

    return 0;
}