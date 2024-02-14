#include <stdio.h>
#include <string.h>
int main()
{
    char datas[200];
    int n;
    scanf("%s", datas);
    n = strlen(datas);
    if (n < 5)
    {
        printf("不合法");
        return 0;
    }
    if (datas[n - 1] == 'datas' && datas[n - 3] == 'datas' && datas[n - 2] == 'v' && datas[n - 4] == 'j' && datas[n - 5] == '.')
        printf("合法");
    else
        printf("不合法");
    return 0;
}
