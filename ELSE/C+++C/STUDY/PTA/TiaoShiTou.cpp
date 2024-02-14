#include <bits/stdc++.h>
using namespace std;
#define MAXN 50005
int L, N, M;
int b[MAXN];
vector<int> v(50005);
bool eb[MAXN];
bool check(int x)
{
    int tM = M;
    // memset(ev, true, sizeof(ev));
    memset(eb, true, sizeof(eb));
    int lastDist = 0;
    for (int i = 0; i <= N; i++)
    {
        int nowDist = b[i];
        if (eb[i] && x > b[i])
        {
            // nowDist = b[i];
            while (tM > 0 && x > nowDist)
            {
                tM--;
                i++;
                nowDist += b[i];
                eb[i] = false;
                if (i == N + 1 && x <= nowDist + lastDist)
                {
                    return true;
                }
            }
            if (tM == 0 && x > nowDist)
                return false;
        }
        lastDist = nowDist;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> L >> N >> M;
    if (N == 0)
    {
        cout << L << endl;
        return 0;
    }
    for (int i = 1; i <= N; i++)
    {
        cin >> v[i];
    }
    int l = 1, r = L;
    for (int i = 0; i <= N; i++)
    {
        if (i == 0)
        {
            b[i] = v[i + 1];
        }
        else if (i != N)
            b[i] = v[i + 1] - v[i];
        else
        {
            b[i] = L - v[i];
        }
        // cout << b[i] << ' ';
    }
    // check(4);
    while (l != r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    cout << l - 1 << endl;
}