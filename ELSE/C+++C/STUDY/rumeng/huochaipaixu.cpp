#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 100005
#define mod 99999997
#define ll long long
int ans;
void merge(long long int list[], long long int temp[], int mid, int left, int right)
{
    int left_p = left, right_p = mid + 1, t_p = left;
    while (left_p <= mid && right_p <= right)
    {
        if (list[left_p] <= list[right_p])
        {
            temp[t_p++] = list[left_p++];
        }
        else
        {
            temp[t_p++] = list[right_p++];
            ans += mid - left_p + 1;
            ans %= mod;
        }
    }
    while (left_p <= mid)
        temp[t_p++] = list[left_p++];
    while (right_p <= right)
        temp[t_p++] = list[right_p++];
    for (int i = left; i <= right; i++)
    {
        list[i] = temp[i];
    }
}
void mesort(long long int list[], long long int temp[], int n, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) >> 1;
        mesort(list, temp, n, left, mid);
        mesort(list, temp, n, mid + 1, right);
        merge(list, temp, mid, left, right);
    }
}
void merg_sort(long long int list[], int n)
{
    long long int *temp = (long long int *)malloc(sizeof(long long int) * (n + 1));
    mesort(list, temp, n, 1, n);
}
struct node
{
    int num, idx;
} first_[MAX], sec_[MAX];
ll a[MAX];
int n;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &first_[i].num);
        first_[i].idx = i;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &sec_[i].num);
        sec_[i].idx = i;
    }
    sort(first_ + 1, first_ + n + 1, [](node a, node b)
         { return a.num < b.num; });
    sort(sec_ + 1, sec_ + n + 1, [](node a, node b)
         { return a.num < b.num; });
    for (int i = 1; i <= n; i++)
    {
        a[first_[i].idx] = sec_[i].idx;
    }
    merg_sort(a, n);
    cout << ans % mod << endl;
}