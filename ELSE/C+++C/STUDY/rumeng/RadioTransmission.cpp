#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
int nexts[MAX];
int len;
char s[MAX];
int main()
{
    int j = 0;
    cin >> len;
    scanf("%s", s + 1);
    for (int i = 2; i <= len; i++)
    {
        while (j && s[j + 1] != s[i])
            j = nexts[j];
        if (s[j + 1] == s[i])
            j++;
        nexts[i] = j;
    }
    // for (int i = 1; i <= len; i++)
    // {
    //     printf("%d ", nexts[i]);
    // }
    printf("%d", len - nexts[len]);
}