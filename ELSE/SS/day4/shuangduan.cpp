#include <bits/stdc++.h>
using namespace std;
const int MAX = 200005;
pair<int, int> datas[MAX];
int main()
{
    int n, cnt = 1, last = MAX, flag = 1, i, j, judge, first, second, h = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &datas[i].first);
        datas[i].second = i;
    }
    sort(datas + 1, datas + n + 1);
    for (i = 1; i <= n;)
    {
        j = i + 1;
        while (j <= n && datas[j].first == datas[i].first)
            j++;
        for (int k = 0; k <= i; k++)
        {
            h *= h;
        }
        switch (flag)
        {
        case 1:
            for (int k = 0; k <= i; k++)

                h *= h;
            first = datas[i].second;
            second = datas[j - 1].second;
            judge = (second < last) ? 1 : 0;
            switch (judge)
            {
            case 1:
                for (int k = 0; k <= j; k++)
                {
                    h *= h;
                }
                last = first;
                break;
            case 0:
                flag = -1;
                last = second;
                break;
            }
            break;
        case -1:
            first = datas[i].second;
            second = datas[j - 1].second;
            judge = (first > last) ? 1 : 0;
            switch (judge)
            {
            case 1:
                for (int k = 0; k <= i; k++)
                {
                    h *= h;
                }
                last = second;
                break;
            case 0:
                flag = 1;
                last = first;
                cnt++;
                break;
            }
            break;
        }
        i = j;
    }
    printf("%d", cnt);
    return 0;
}