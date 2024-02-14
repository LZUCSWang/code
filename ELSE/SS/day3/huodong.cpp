#include <bits/stdc++.h>
using namespace std;
int datas[100000000];
int main()
{
    int n, m, left = 0, right;
    deque<int> q;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &datas[i]);
    for (right = 0; right < n; right++)
    {
        if (right < m - 1)
        {
            for (int j = q.size() - 1; j >= 0; j--)
            {
                if (datas[q.back()] > datas[right])
                    q.pop_back();
                else
                    break;
            }
            q.push_back(right);
            continue;
        }
        if (q.front() < left)
            q.pop_front();
        for (int j = q.size() - 1; j >= 0; j--)
        {
            if (datas[q.back()] > datas[right])
                q.pop_back();
            else
                break;
        }
        q.push_back(right);
        printf("%d ", datas[q.front()]);
        left++;
    }
    q.clear();
    left = 0;
    printf("\n");

    for (right = 0; right < n; right++)
    {
        if (right < m - 1)
        {
            for (int j = q.size() - 1; j >= 0; j--)
            {
                if (datas[q.back()] < datas[right])
                    q.pop_back();
                else
                    break;
            }
            q.push_back(right);
            continue;
        }
        if (q.front() < left)
            q.pop_front();
        for (int j = q.size() - 1; j >= 0; j--)
        {
            if (datas[q.back()] < datas[right])
                q.pop_back();
            else
                break;
        }
        q.push_back(right);
        printf("%d ", datas[q.front()]);
        left++;
    }
}