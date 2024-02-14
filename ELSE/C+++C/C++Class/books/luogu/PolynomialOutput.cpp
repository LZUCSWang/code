#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, temp, i = 1;
    cin >> n;
    if (n != 0)
    {
        cin >> temp;
        if (n != 1)
            if (temp == 1)
                printf("x^%d", (n - i + 1));
            else if (temp == -1)
                printf("-x^%d", (n - i + 1));
            else
                printf("%dx^%d", temp, (n - i + 1));
        else if (temp == 1)
            printf("x");
        else if (temp == -1)
            printf("-x");
        else
            printf("%dx", temp);
        for (int i = 2; i <= n; i++)
        {
            cin >> temp;
            if (temp == 0)
                continue;
            if (temp > 0 && abs(temp) != 1)
                if (n - i + 1 != 1)
                    printf("+%dx^%d", temp, (n - i + 1));
                else
                    printf("+%dx", temp);
            else if (temp == 1)
                if (n + 1 - i != 1)
                    printf("+x^%d", n - i + 1);
                else
                    printf("+x");
            // printf("+x^%d", (n - i + 1));
            else if (temp == -1)
                if (n - i + 1 != 1)
                    printf("-x^%d", (n - i + 1));
                else
                    printf("-x");
            // printf("-x^%d", (n - i + 1));
            else if (n - i + 1 != 1)
                printf("%dx^%d", temp, (n - i + 1));
            else
                printf("%dx", temp);
        }
    }
    cin >> temp;
    if (n == 0)
    {
        printf("%d", temp);
        return 0;
    }
    if (temp == 0)
        return 0;
    if (temp > 0 && abs(temp) != 1)
        printf("+%d", temp);
    else if (temp == 1)
        printf("+1");
    else if (temp == -1)
        printf("-1");
    else
        printf("%d", temp);
}