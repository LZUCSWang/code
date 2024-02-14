#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10000001
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", i);
    }
    for (int i = 1; i <= n; i += 2)
    {
        printf("%d ", i);
    }
    for (int i = 2; i <= n; i += 2)
    {
        printf("%d ", i);
    }
}