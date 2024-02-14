#include <bits/stdc++.h>
using namespace std;
#define MAX 219
int rules[5][5] = {
    {0, 0, 1, 1, 0},
    {1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 0, 1},
    {1, 1, 0, 0, 0}};
int aa[MAX], bb[MAX];
int main()
{
    int n, datas, b;
    cin >> n >> datas >> b;
    int cnta = 0, cntb = 0;
    for (int i = 0; i < datas; i++)
    {
        cin >> aa[i];
    }
    for (int i = 0; i < b; i++)
    {
        cin >> bb[i];
    }
    for (int i = 0; i < n; i++)
    {
        cnta += rules[aa[i % datas]][bb[i % b]];
        cntb += rules[bb[i % b]][aa[i % datas]];
    }
    cout << cnta << " " << cntb << endl;
}