#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
// 24
// 00001 M 01111 -1
// 00002 F 02222 03333
// 00003 M 02222 03333
// 00004 F 04444 03333
// 00005 M 04444 05555
// 00006 F 04444 05555
// 00007 F 06666 07777
// 00008 M 06666 07777
// 00009 M 00001 00002
// 00010 M 00003 00006
// 00011 F 00005 00007
// 00012 F 00008 08888
// 00013 F 00009 00011
// 00014 M 00010 09999
// 00015 M 00010 09999
// 00016 M 10000 00012
// 00017 F -1 00012
// 00018 F 11000 00013
// 00019 F 11100 00018
// 00020 F 00015 11110
// 00021 M 11100 00020
// 00022 M 00016 -1
// 00023 M 10012 00017
// 00024 M 00022 10013
// 9
// 00021 00024
// 00019 00024
// 00011 00012
// 00022 00018
// 00001 00004
// 00013 00016
// 00017 00015
// 00019 00021
// 00010 00011
vector<int> v[MAX];
int seen[MAX], n, m;
bool flag, sex[MAX];
void dfs(int from, int num)
{
    if (num >= 4)
    {
        return;
    }
    for (int i = 0; i < v[from].size(); i++)
    {
        int parent = v[from][i];
        if (!seen[parent])
        {
            seen[parent] = 1;
            dfs(parent, num + 1);
        }
        else
        {
            flag = true;
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int id, fa_id, ma_id;
        char sex_;
        cin >> id >> sex_ >> fa_id >> ma_id;
        if (sex_ == 'M')
        {
            sex[id] = true;
        }
        if (fa_id != -1)
        {
            v[id].push_back(fa_id);
            sex[fa_id] = true;
        }
        if (ma_id != -1)
        {
            v[id].push_back(ma_id);
        }
    }
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        if (sex[x] == sex[y])
        {
            cout << "Never Mind" << endl;
            continue;
        }
        memset(seen, 0, MAX * 4);
        flag = false;
        seen[x] = 1;
        seen[y] = 1;
        dfs(x, 0);
        dfs(y, 0);
        if (flag)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
        }
    }
}