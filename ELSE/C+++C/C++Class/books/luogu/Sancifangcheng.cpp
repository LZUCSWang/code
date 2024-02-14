#include <bits/stdc++.h>
using namespace std;
double datas, b, c, d;
double f(double x)
{
    return datas * x * x * x + b * x * x + c * x + d;
}
int main()
{
    int cnt = 0;
    cin >> datas >> b >> c >> d;
    for (int i = -100; i < 100; i++)
    {
        double l = i, r = i + 1;
        if (!f(i))
        {
            printf("%.2lf ", l);
            cnt++;
        }
        if (f(i) * f(i + 1) < 0)
        {

            // double l = i, r = i + 1;
            while (r - l >= 0.001)
            {
                double mid = (l + r) / 2;
                if (f(mid) * f(r) < 0)
                    l = mid;
                else
                    r = mid;
            }
            printf("%.2lf ", r);
            cnt++;
        }
        if (cnt == 3)
            return 0;
    }
}