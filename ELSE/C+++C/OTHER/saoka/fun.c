#include <stdio.h>
#include <math.h>

int main()
{
    double x, f;
    if (!scanf("%lf", &x))
    {
        printf("Input error:(\n");
        return 0;
    }
    if (x <= 0)
        f = sqrt(fabs(3 * x + 1));
    else if (x <= 5)
        f = 4 * sin(x) + 2;
    else
        f = 5 * x * x * x + 3;
    return 0 & printf("%lf\n", f);
}