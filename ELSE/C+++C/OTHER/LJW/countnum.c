#include <stdio.h>
int main()
{
    int input, arr[10] = {0}, k = 0;
    scanf("%d", &input);
    while (input)
    {
        arr[input % 10]++;
        input /= 10;
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d:%d\n", i, arr[i]);
    }
}