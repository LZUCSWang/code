#include<stdio.h>
#define PI 3.14159
int main(){
    double r,h;
    printf("请输入圆的半径和圆柱的高:");
    scanf("%lf,%lf",&r,&h);
    printf("圆的周长=%.2lf,圆的面积=%.2lf,圆柱的体积=%.2lf,圆球的表面积=%.2lf,圆球的体积=%.2lf",2*PI*r,PI*r*r,PI*r*r*h,4*PI*r*r,4/3*PI*r*r*r);
}