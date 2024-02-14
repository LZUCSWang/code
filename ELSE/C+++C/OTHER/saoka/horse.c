#include <stdio.h>
int main()
{
 double x=87,y=72,z=90,a;
 scanf("%lf,%lf,%lf",&x,&y,&z);
 a=(x+y+z)/3.0;
 printf("数学成绩=%.1f,英语成绩=%.1f,计算机成绩=%.1f,平均成绩=%.1f",x,y,z,a);
 return 0;
}
