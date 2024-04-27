#include <bits/stdc++.h>
using namespace std;
#define MAX 10000000
char a[MAX], b[MAX];
int nexts[MAX];
int len_b, len_a;
void input()
{
    scanf("%s", a + 1);
    scanf("%s", b + 1);
}
void getnext()
{
    int j = 0;
    len_b = strlen(b + 1);
    for (int i = 2; i <= len_b; i++)
    {
        while (j && b[j + 1] != b[i])
        {
            j = nexts[j];
        }
        if (b[j + 1] == b[i])
        {
            j++;
        }
        nexts[i] = j;
    }
}
void KMP()
{
    int j = 0;
    len_a = strlen(a + 1);
    for (int i = 1; i <= len_a; i++)
    {
        while (j && a[i] != b[j + 1])
        {
            j = nexts[j];
        }
        if (a[i] == b[j + 1])
        {
            j++;
        }
        if (j == len_b)
        {
            printf("%d\n", i + 1 - j);
            j = nexts[j];
        }
    }
    for (int i = 1; i <= len_b; i++)
    {
        printf("%d ", nexts[i]);
    }
}
int main()
{
    input();
    getnext();
    KMP();
}