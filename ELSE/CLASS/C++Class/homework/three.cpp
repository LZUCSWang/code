#include <bits/stdc++.h>
using namespace std;
#define N 100000
#define INF 2e9
#define MAX 30
vector<int> nums;
int n, target;
int main()
{
    scanf("%d %d", &n, &target);
    for (int i = 0; i < n; ++i)
    {
        int a;
        scanf("%d", &a);
        nums.push_back(a);
    }
    sort(nums.begin(), nums.end());
    int ret = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < n; i++)
    {
        int low = i + 1, high = n - 1;
        while (low < high)
        {
            int tmp = nums[i] + nums[low] + nums[high];
            if (abs(target - tmp) < abs(target - ret))
                ret = tmp;
            if (tmp < target)
                low++;
            else if (tmp > target)
                high--;
            else
            {
                ret = target;
                break;
            }
        }
    }
    printf("%d", ret);
}
