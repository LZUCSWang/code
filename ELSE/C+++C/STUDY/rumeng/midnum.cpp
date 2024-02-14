#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000

// 7
// 1 3 5 7 9 11 6

int n;
vector<int> v;
int main()
{
    cin >> n;
    for (int i = 1, a; i <= n; i++)
    {
        scanf("%d", &a);
        v.insert(upper_bound(v.begin(), v.end(), a), a);
        if (i & 1)
        {
            cout << v[i / 2] << endl;
        }
    }
    // for (int i = 0; i < v.size(); i++)
    //     cout << v[i] << ' ';
}