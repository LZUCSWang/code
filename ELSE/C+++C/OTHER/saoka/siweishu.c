#include <stdio.h>
int main()
{
    int a;
    printf("Please input a number with 4 digit:");
    scanf("%d", &a);
    a = a > 0 ? a : -a;
    int sum = a % 10 + a / 10 % 10 + a / 100 % 10 + a / 1000;
    printf("Ones place:%d\n", a % 10);
    printf("Tens place:%d\n", a / 10 % 10);
    printf("Hundreds place:%d\n", a / 100 % 10);
    printf("Thousands place:%d\n", a / 1000 % 10);
    printf("The sum of all numbers:%d\n", sum);
    return 0;
}