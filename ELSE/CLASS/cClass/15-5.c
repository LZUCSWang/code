/*编写一个函数，把一个 unsigned int 类型值中的所有位向左旋转指定数量的位。
例如，rotate_l(x, 4)把x中所有位向左移动4个位置，而且从最左端移出的位会重新出现在右端。
也就是说，把高阶位移出的位放入低阶位。在一个程序中测试该函数。*/
#include<stdio.h>
#include<math.h>
unsigned int fun(unsigned int num,int wei){
    while(wei>0){
        if(num>=2147483648){
            num=((num-2147483648)<<1)+1;
        }
        else num=num<<1;
        wei--;
    }
    return num;
}
int main(){
    unsigned int num;
    int wei;
    scanf("%u %d",&num,&wei);
    printf("%u",fun(num,wei));
}