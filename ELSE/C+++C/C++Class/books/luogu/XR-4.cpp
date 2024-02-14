    #include <bits/stdc++.h>
    #include <algorithm>
    using namespace std;
    #define MAX 100000

    int main()
    {
        int n, m, k, t;
        cin >> n >> m >> k;
        int cnt[k + 1] = {0},visited[m + 1][MAX] = {0};
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> t;
                if (visited[j][t] == 0)
                {
                    visited[j][t] = 1;
                    cnt[t]++;
                }
            }
        }
        for (int i = 1; i <= k; i++)
        {
            cout << cnt[i] << " ";
        }
    }