#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int lengthOfLongestSubstring(char *s)
{
    int i;
    int count = 1;
    char *p, *q;
    int n = strlen(s);
    int datas[n];
    printf("%d\n", n);
    for (i = 0; i < n - 1; i++)
    {
        q = &s[i];
        p = q + 1;
        while (*p != '\0')
        {

            if ((*(p++) != *q))
            {
                count++;
            }
            else
            {
                datas[i] = count;
                count = 1;
            }
        }
    }

    int temp = datas[0];
    for (i = 0; i < n - 1; i++)
    {
        printf("%d ", datas[i]);
        if (temp < datas[i])
            temp = datas[i];
    }
    return temp;
}
int main()
{
    char *str = "abcabcbb";
    int length = lengthOfLongestSubstring(str);
    printf("The max string's length is %d\n ", length);
    system("pause"); 
    return 0;
}
