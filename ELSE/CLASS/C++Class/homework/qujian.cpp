#include <bits/stdc++.h>
using namespace std;
#define N 100000
#define INF 2e9
#define MAX 30
int n;
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    if (n == 1)
        return intervals;
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (i == n - 1)
            res.push_back(vector<int>{intervals[i][0], intervals[i][1]});
        for (j = i + 1; j < n; j++)
        {
            if (intervals[j][0] <= intervals[i][1])
            {
                intervals[i][1] = max(intervals[i][1], intervals[j][1]);
                if (j == n - 1)
                {
                    res.push_back(vector<int>{intervals[i][0], intervals[i][1]});
                    i = n - 1;
                    break;
                }
            }
            else
            {
                res.push_back(vector<int>{intervals[i][0], intervals[i][1]});
                i = j - 1;

                break;
            }
        }
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    vector<vector<int>> intervals;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        intervals.push_back(vector<int>{a, b});
    }
    vector<vector<int>> res = merge(intervals);
    for (int i = 0; i < res.size(); ++i)
    {
        printf("%d %d\n", res[i][0], res[i][1]);
    }
}
