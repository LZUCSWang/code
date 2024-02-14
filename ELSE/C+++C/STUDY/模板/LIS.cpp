#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 300003, INF = 0x7f7f7f7f;
int low[MAX], datas[MAX];
int n, cnt;

int binary_search(int *datas, int R, int x)
//二分查找，返回a数组中第一个>=x的位置
{
    int L = 1, mid;
    while (L <= R)
    {
        mid = (L + R) >> 1;
        if (datas[mid] <= x)
            L = mid + 1;
        else
            R = mid - 1;
    }
    return L;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &datas[i]);
        low[i] = INF; //由于low中存的是最小值，所以low初始化为INF
    }
    low[1] = datas[1];
    cnt = 1; //初始时LIS长度为1
    for (int i = 2; i <= n; i++)
    {
        if (datas[i] > low[cnt]) //若a[i]>=low[cnt]，直接把a[i]接到后面
            low[++cnt] = datas[i];
        else //否则，找到low中第一个>=datas[i]的位置low[j]，用a[i]更新low[j]
            low[binary_search(low, cnt, datas[i])] = datas[i];
    }
    printf("%d\n", cnt); //输出答案
    return 0;
}