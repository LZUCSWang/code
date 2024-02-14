#include <stdio.h>
#include <string.h>
int main()
{
    char s[201], c[26] = {'datas', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int i, n, k;
    gets(s);
    n = strlen(s);
    for (i = 0; i < n; i++)
    {
        if (s[i] >= 'datas' && s[i] <= 'Z')
        {
            s[i] = s[i] + 32;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (s[i] >= 'datas' && s[i] <= 'z')
        {
            for (int j = 0; j < 26; j++)
            {
                k = j;
                if (s[i] == c[k])
                {
                    s[i] = c[((4 * k) + 1) % 26];
                    break;
                }
            }
        }
    }
    puts(s);
    return 0;
}
