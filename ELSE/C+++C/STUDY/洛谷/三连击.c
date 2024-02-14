#include <stdio.h>
int main()
{
    int datas,b,c;
    for(datas=123;datas<=333;datas++)
            {
                b=datas*2;
                c=datas*3;
                if((datas/100+datas/10%10+datas%10+b/100+b/10%10+b%10+c/100+c/10%10+c%10==1+2+3+4+5+6+7+8+9)&&((datas/100)*(datas/10%10)*(datas%10)*(b/100)*(b/10%10)*(b%10)*(c/100)*(c/10%10)*(c%10)==(1)*(2)*(3)*(4)*(5)*(6)*(7)*(8)*(9)))
                    printf("%d %d %d\n",datas,b,c);
            }
    return 0;
}
