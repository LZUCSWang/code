#include <stdio.h>
double a, b, c, disc, x1, x2, p, q;
void xiao()
{
    x1 = x2 = -b / (2 * a);
    printf("方程有两个相等的实根:%8.4lf", x1);
}
void den()
{
    p = -b / (2 * a);
    q = sqrt(-disc) / (2 * a);
    printf("方程有两个共轭复根:%8.4lf+%8.4lfi和%8.4lf-%8.4lfi", p, q, p, q);
}
void da()
{
    p = -b / (2 * a);
    q = sqrt(disc) / (2 * a);
    x1 = p + q;
    x2 = p - q;
    printf("方程有两个不等的实根:%8.4lf和%8.4lf", x1, x2);
}
int main()
{

    printf("请输入a,b,c的值:");
    scanf("%lf,%lf,%lf", &a, &b, &c);
    printf("方程为:%5.2lfx*x+%5.2lfx+%5.2lf=0", a, b, c);
    disc = b * b - 4 * a * c;
    if (disc == 0)
    {
        den();
    }
    else if (disc > 0)
    {
        da();
    }
    else
    {
        xiao();
    }
    return 0;
}
