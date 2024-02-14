#include <stdio.h>
#define ull unsigned long long
// 猴子吃桃问题
// 猴子第一天摘下若干个桃子，当即吃了一半，还不瘾，又多吃了一个；第二天早上又将剩下的桃子吃掉一半，又多吃了一个；以后每天早上都吃了前一天剩下的一半零一个；
// 到第n天早上想再吃时，见只剩下一个桃子了。求第一天共摘了多少。
// 编程实现：从键盘输入第n天，计算猴子第一天摘了多少个桃子。
int main()
{
    int n;
    ull ans = 1;
    if (!scanf("%d", &n))
        return 0 & printf("Input error:(\n");
    for (int i = n; i > 1; i--)
        ans = ans * 2 + 2;
    return 0 & printf("%llu\n", ans);
}