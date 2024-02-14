#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m;
PII stk[N];
int ans[N];

int main()
{
    scanf("%d%d", &n, &m);
    int top = 0;
    while (m--)
    {
        int p, q;
        scanf("%d%d", &p, &q);
        if (!p) // 操作1
        {
            while (top && stk[top].x == 0)
                q = max(q, stk[top--].y); // 出现连续的操作1，我们取最大
            while (top >= 2 && stk[top - 1].y <= q)
                // 如果当前的操作1比上一次的操作1范围大，则将上一次操作1和操作2删除
                top -= 2;
            stk[++top] = {0, q}; // 存本次最佳操作
        }
        else if (top) // 操作2 &&且操作1已经进行过（操作二第一个用没效果）
        {
            while (top && stk[top].x == 1)
                q = min(q, stk[top--].y);
            while (top >= 2 && stk[top - 1].y >= q)
                top -= 2;
            stk[++top] = {1, q};
        }
    }
    int k = n, l = 1, r = n;
    for (int i = 1; i <= top; i++)
    {
        if (stk[i].x == 0) // 如果是操作1
            while (r > stk[i].y && l <= r)
                ans[r--] = k--; // 移动r值 ，并赋值
        else
            while (l < stk[i].y && l <= r)
                ans[l++] = k--;
        if (l > r)
            break;
    }
    if (top % 2)
        while (l <= r)
            ans[l++] = k--;
    else
        while (l <= r)
            ans[r--] = k--;

    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}
