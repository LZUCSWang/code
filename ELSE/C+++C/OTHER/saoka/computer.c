#include <stdio.h>

int main()
{
    double x, y, ans;
    printf("Enter number(x y):");
    if (scanf("%lf %lf", &x, &y) != 2)
    {
        printf("Input error:(\n");
        return 0;
    }
    printf("Enter operator(+ - * /):");
    char op;
    if (!scanf(" %c", &op))
    {
        printf("Input error:(\n");
        return 0;
    }
    int flag = 0;
    printf("Input the compute mode(1 for if...else, 0 for switch...case): ");
    if (!scanf("%d", &flag))
    {
        printf("Input error:(\n");
        return 0;
    }
    if (flag)
    {
        if (op == '+')
            ans = x + y;
        else if (op == '-')
            ans = x - y;
        else if (op == '*')
            ans = x * y;
        else if (op == '/')
        {
            if (y == 0)
                printf("Divide by zero!:(\n");
            else
                ans = x / y;
        }
        else
        {
            printf("Input error:(\n");
            return 0;
        }
    }
    else
    {
        switch (op)
        {
        case '+':
            ans = x + y;
            break;
        case '-':
            ans = x - y;
            break;
        case '*':
            ans = x * y;
            break;
        case '/':
            if (y == 0)
            {
                printf("Divide by zero!:(\n");
                return 0;
            }
            ans = x / y;
            break;
        default:
            printf("Input error:(\n");
            return 0;
        }
    }
    printf("%lf %c %lf = %lf:)\n", x, op, y, ans);
    return 0;
}