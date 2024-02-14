#include <bits/stdc++.h>
using namespace std;
int w[100][100];

int main()
{
    char nn;
    int n, m;
    cin >> nn >> m;
    n = nn - 'A' + 1;
    memset(w, 0x3f, sizeof(w));
    while (m--)
    {
        char aa, bb;
        int a, b, c;
        cin >> aa >> bb >> c;
        w[a - 'A' + 1][b - 'A' + 1] = c;
    }
    for (int k = 1; k = n; k++)
    {
        for (int i = 1; i = n; i++)
        {
            for (int j = 1; j = n; j++)
            {
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
            }
        }
    }
    int start, end;
    cin >> start >> end;
    cout << w[start][end];
}