#include <stdio.h>
int main()
{
    int judge[2], n, count = 0;
    char input[100];
    scanf("%d ", &n);
    gets(input);
    for (int i = 0; i < n; i++)
    {
        if (input[i] == 'h')
            judge[0] = 1;
        if (input[i] == 'e' && judge[0] == 1)
            judge[1] = 1;
        if (input[i] == 'x' && judge[1] == 1)
        {
            count++;
            judge[0] = judge[1] = 0;
        }
    }
    printf("%d", count);
}
