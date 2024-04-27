#include <bits/stdc++.h>
using namespace std;
#define N 100000
#define INF 2e9
#define MAX 30
int n, k;
int arr[N];
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);
    scanf("%d", &k);
    int wins = 0, i = 0, j = 1;
    while (n-- && n > 0)
    {
        if (wins == k)
            break;
        if (arr[i] > arr[j])
            wins++;
        else
        {
            i = j;
            wins = 1;
        }
        j++;
    }
    printf("%d", arr[i]);
}
