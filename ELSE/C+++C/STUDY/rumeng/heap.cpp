#include <bits/stdc++.h>
using namespace std;
priority_queue<int, vector<int>, greater<int>> q;
int n;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            int t;
            scanf("%d", &t);
            q.push(t);
        }
        else if (choice == 2)
        {
            printf("%d\n", q.top());
        }
        else
        {
            q.pop();
        }
    }
}