#include <stdio.h>
#include <stdlib.h>
typedef struct complex
{
    double real;
    double imag;
}complex;

complex plus(complex a, complex b)
{
    complex ret;
    ret.real = a.real + b.real;
    ret.imag = a.imag + b.imag;
    return ret;
}

complex mul(complex a, complex b)
{
    complex ret;
    ret.real = a.real * b.real - a.imag * b.imag;
    ret.imag = a.real * b.imag + a.imag * b.real;
    return ret;
}
complex divi(complex a, complex b)
{
    complex temp;
    temp.real = b.real;
    temp.imag = -b.imag;
    complex ret = mul(a, temp);
    double num = b.real * b.real + b.imag * b.imag;
    ret.real /= num;
    ret.imag /= num;
    return ret;
}
int main()
{
    complex A,B;
    A.real=8,A.imag=6,B.real=4,B.imag=3;
    complex up = mul(A, B);
    complex down = plus(A, B); 
    complex ans = divi(up, down);
    printf("%.2lf", ans.real);
    ans.imag==0?printf(""):ans.imag>0?printf("+%.2lfi", ans.imag):printf("%.2lfi", ans.imag);
    return 0;
}