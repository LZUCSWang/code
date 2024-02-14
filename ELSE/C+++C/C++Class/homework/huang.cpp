#include <bits/stdc++.h>
using namespace std;
#define N 100000
#define INF 2e9
#define MAX 30
int i, fin, k, m, beg;
int ck(int remain)
{
    int result = (beg + m - 1) % remain;
    if (result >= k)
    {
        beg = result;
        return 1;
    }
    else
        return 0;
}
int main()
{
    scanf("%ld", &k);
    m = k;
    while (!fin)
    {
        fin = 1;
        beg = 0;
        for (i = 0; i < k; i++)
            if (!ck(2 * k - i))
            {
                fin = 0;
                break;
            }
        m++;
    }
    printf("%d", m - 1);
    return 0;
}