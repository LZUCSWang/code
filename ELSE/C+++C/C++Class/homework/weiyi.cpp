#include <bits/stdc++.h>
using namespace std;
#define N 100000
#define INF 2e9
#define MAX 30

int firstUniqChar(char *s)
{
    int arr[26] = {0};
    int len = strlen(s);
    int n = 0;
    for (int i = 0; i < len; ++i)
    {
        arr[(s[i] - 'a')]++;
    }
    for (int i = 0; i < len; ++i)
    {
        if (arr[(s[i] - 'a')] == 1)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    char s[N];
    scanf("%s", s);
    printf("%d", firstUniqChar(s));
}