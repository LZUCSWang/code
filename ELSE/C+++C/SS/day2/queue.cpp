#include<bits/stdc++.h>
using namespace std;
int main()
{
    deque<int> q1, q2;
    FILE *f = fopen("./right.txt", "w");
    int m, n, num;
    scanf("%d %d", &m, &n);
    char str[20];
    for (int i = 0; i < m; i++)
    {
        scanf("%s", &str);
        if (strcmp(str, "EnQueue") == 0)
        {
            scanf("%d", &num);
            if (q1.size() + q2.size() >= n)
            {
                printf("Full Queue\n");
                fprintf(f, "Full Queue\n");
                continue;
            }
            q2.push_back(num);
            if (q1.size() < q2.size())
            {
                q1.push_back(q2.front());
                q2.pop_front();
            }
        }
        else
        {
            if (q1.size() == 0)
            {
                printf("Empty Queue\n");
                fprintf(f, "Empty Queue\n");
                continue;
            }
            if (strcmp(str, "DeQueue") == 0)
            {
                int t=q1.front();
                printf("%d\n", t);
                fprintf(f,"%d\n", t);
                q1.pop_front();
                if (q1.size() < q2.size())
                {
                    q1.push_back(q2.front());
                    q2.pop_front();
                }
            }
            else
            {
                int t = q1.back();
                printf("%d\n", t);
                fprintf(f, "%d\n", t);
                q1.pop_back();
                if (q1.size() < q2.size())
                {
                    q1.push_back(q2.front());
                    q2.pop_front();
                }
            }
        }
    }
    for (int i = 0; i < q1.size(); i++)
    {
        if (i)
        {
            printf(" ");
            fprintf(f, " ");
        }
        printf("%d", q1[i]);
        fprintf(f, "%d", q1[i]);
    }
    for (int i = 0; i < q2.size(); i++)
    {
        printf(" %d", q2[i]);
        fprintf(f, " %d", q2[i]);
    }
    return 0;
}