#include <bits/stdc++.h>
using namespace std;
priority_queue<int, vector<int>, greater<int>> q;
int main()
{
    int n, op, num;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d", &num);
            q.push(num);
        }
        else if (op == 2)
        {
            printf("%d\n", q.top());
        }
        else if (op == 3)
        {
            q.pop();
        }
    }
}