#include <bits/stdc++.h>
using namespace std;
deque<long long> q;
long long n, m;
#define MAX 10000001
long long datas[MAX];
void maxslidingwindow()
{
    long long left = 1, right;
    for (right = 1; right <= n; right++)
    {
        while (q.size() > 0 && datas[right] >= datas[q.back()])
        {
            q.pop_back();
        }
        q.push_back(right);
        if (q.front() < left)
        {
            q.pop_front();
        }
        if (right>= m)
        {
            printf("%lld ", datas[q.front()]);
            left++;
        }
    }
}
void minslidingwindow()
{
    long long left = 1, right;
    for (right = 1; right <= n; right++)
    {
        while (q.size() > 0 && datas[right] <= datas[q.back()])
        {
            q.pop_back();
        }
        q.push_back(right);
        if (q.front() < left)
        {
            q.pop_front();
        }
        if (right >= m)
        {
            printf("%lld ", datas[q.front()]);
            left++;
        }
    }
}
void input()
{
    cin >> n >> m;
    for (long long i = 1; i <= n; i++)
    {
        scanf("%lld", &datas[i]);
    }
}
int  main()
{
    input();
    minslidingwindow();
    putchar('\n');
    q.clear();
    maxslidingwindow();
}