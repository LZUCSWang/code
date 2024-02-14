#include <stdio.h>
#include <stdlib.h>
double *plus(double a[], double b[])
{
    double *ret = (double *)malloc(sizeof(double) * 2);
    ret[0] = a[0] + b[0];
    ret[1] = a[1] + b[1];
    return ret;
}
double *mul(double a[], double b[])
{
    double *ret = (double *)malloc(sizeof(double) * 2);
    ret[0] = a[0] * b[0] - a[1] * b[1];
    ret[1] = a[0] * b[1] + a[1] * b[0];
    return ret;
}
double *divi(double a[], double b[])
{
    double temp[] = {b[0], -b[1]};
    double *ret = mul(a, temp);
    double num = b[0] * b[0] + b[1] * b[1];
    ret[0] /= num;
    ret[1] /= num;
    return ret;
}
int main()
{
    double a[] = {8, 6}, b[] = {4, 3};
    double *up = mul(a, b);
    double *down = plus(a, b); 
    double *ans = divi(up, down);
    printf("%.2lf", ans[0]);
    ans[1]==0?printf(""):ans[1]>0?printf("+%.2lfi", ans[1]):printf("%.2lfi", ans[1]);
    free(up);
    free(down);
    free(ans);
    return 0;
}