#include <stdio.h>
#include <string.h>
#define MAX 10000001
char s[MAX], t[MAX];
int nextval[MAX];
int next[MAX];
int len_t, len_s;
void KMP()
{
    int i = 0, j = 0;
    while (i < len_s)
    {

        while (i < len_s && j < len_t)
        {
            if (j == -1 || s[i] == t[j])
            {
                i++;
                j++;
            }
            else
            {
                j = nextval[j];
            }
        }
        if (j == len_t)
        {
            printf("%d\n", i - len_t + 1);
            j = 0;
            i = i - len_t + 1;
        }
        else
            break;
    }
}
void input()
{
    scanf("%s", s);
    scanf("%s", t);
    len_t = strlen(t), len_s = strlen(s);
    int i = 0, j = -1;
    next[0] = -1;
    while (i < len_t)
    {
        if (j == -1 || t[i] == t[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    i = 0, j = -1;
    nextval[0] = -1;
    while (i < len_t)
    {
        if (j == -1 || t[i] == t[j])
        {
            j++;
            i++;
            if (t[j] != t[i])
            {
                nextval[i] = j;
            }
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}
int main()
{
    input();
    KMP();
    for (int i = 1; i <= strlen(t); i++)
    {
        printf("%d", next[i]);
        if (i != strlen(t))
            printf(" ");
    }
    return 0;
}