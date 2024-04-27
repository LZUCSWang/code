#include <bits/stdc++.h>
#define MAX 100000001
using namespace std;
long long int lists1[MAX];
long long int ans = 0;
void print(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", list[i]);
        if (i != n - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}
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
    long long int *temp = (long long int *)malloc(sizeof(long long int) * (n+1));
    mesort(list, temp, n, 1, n);
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &lists1[i]);
    }
    merg_sort(lists1,n);
    printf("%lld", ans);
}