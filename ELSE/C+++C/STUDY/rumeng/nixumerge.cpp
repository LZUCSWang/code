#include <bits/stdc++.h>
using namespace std;
long long ans;
#define MAX 100000001
void msort(long long lists[], long long temp[], long long left, long long right)
{
    long long t_p = left, l_p = left, mid = (left + right) >> 1, r_p = mid + 1;
    while (l_p <= mid && r_p <= right)
    {
        if (lists[l_p] <= lists[r_p])
        {
            temp[t_p++] = lists[l_p++];
        }
        else
        {
            temp[t_p++] = lists[r_p++];
            ans += mid - l_p + 1;
        }
    }
    while (l_p <= mid)
    {
        temp[t_p++] = lists[l_p++];
    }
    while (r_p <= right)
    {
        temp[t_p++] = lists[r_p++];
    }
    for (long long i = left; i <= right; i++)
    {
        lists[i] = temp[i];
    }
}
void merge(long long lists[], long long temp[], long long left, long long right)
{
    if (left < right)
    {
        long long mid = (left + right) >> 1;
        merge(lists, temp, left, mid);
        merge(lists, temp, mid + 1, right);
        msort(lists, temp, left, right);
    }
}
long long temp[MAX], lists[MAX];
int main()
{
    long long n;
    cin >> n;
    for (long long i = 0; i < n; i++)
    {
        scanf("%d", &lists[i]);
    }
    merge(lists, temp, 0, n - 1);
    printf("%d", ans);
}