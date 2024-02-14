#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    enum color
    {
        red,
        blue = 3,
        green
    };
    enum color c;
    for (c = blue; c < green; c++)
    {
        printf("%d\n", c);
    }
}