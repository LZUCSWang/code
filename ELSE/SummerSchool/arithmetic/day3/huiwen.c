#include <stdio.h>
#include <string.h>

int main()
{
    char input[100000];
    scanf("%s", input);
    int left = 0, right = strlen(input) - 1;
    while (left < right)
    {
        if (input[left] != input[right])
        {
            printf("no\n");
            return 0;
        }
        left++;
        right--;
    }
    printf("yes\n");
}