#include <bits/stdc++.h>
using namespace std;
#define MAX 1005
char str[MAX];
int main()
{
    // scanf("%s", str);
    fgets(str, MAX, stdin);
    int len = strlen(str);
    for (int width = len; width >= 1; width--)
    {
        for (int start = 0; start + width < len; start++)
        {
            int left = start, right = start + width - 1;
            while (left < right && str[left] == str[right])
            {
                left++;
                right--;
            }
            if (left >= right)
            {
                printf("%d\n", width);
                return 0;
            }
        }
    }
}