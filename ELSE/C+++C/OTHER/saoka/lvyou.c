#include <stdio.h>
#include <string.h>
int main()
{
    int input;
    scanf("%d", &input);
    char place[input][21];
    for (int i = 0; i < input; i++)
    {
        scanf("%s", place[i]);
    }
    char target[21];
    int count = 0;
    scanf("%s", target);
    for (int i = 0; i < input; i++)
    {
        if (strcmp(place[i], target) == 0)
            count++;
    }
    printf("%d", count);
