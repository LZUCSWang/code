#include <iostream>
#include <algorithm>
using namespace std;
int n, r, q;
int datas[200100], win[200100], lose[200100];
int s[200100], w[200100];
bool cmp(int x, int y)
{
    if (s[x] == s[y])
        return x < y;
    return s[x] > s[y];
}
void merge()
{
    int i, j;
    i = j = 1, datas[0] = 0;
    while (i <= win[0] && j <= lose[0])
        if (cmp(win[i], lose[j]))
            datas[++datas[0]] = win[i++];
        else
            datas[++datas[0]] = lose[j++];
    while (i <= win[0])
        datas[++datas[0]] = win[i++];
    while (j <= lose[0])
        datas[++datas[0]] = lose[j++];
}
int main()
{
    cin >> n >> r >> q;
    n *= 2;
    for (int i = 1; i <= n; i++)
        datas[i] = i;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    sort(datas + 1, datas + n + 1, cmp);
    for (int i = 1; i <= r; i++)
    {
        win[0] = lose[0] = 0;
        for (int j = 1; j <= n; j += 2)
            if (w[datas[j]] > w[datas[j + 1]])
            {
                s[datas[j]]++;
                win[++win[0]] = datas[j];
                lose[++lose[0]] = datas[j + 1];
            }
            else
            {
                s[datas[j + 1]]++;
                win[++win[0]] = datas[j + 1];
                lose[++lose[0]] = datas[j];
            }
        merge();
    }
    cout << datas[q];
    return 0;
}