#include <stdio.h>
#include <string.h>
int main()
{
    int num, sum = 0;
    char target[] = "370211";
    char shenfen[19];
    scanf("%d", &num);
    getchar();
    for (int i = 0; i < num; i++)
    {
        int flag = 1;
        for (int j = 0; j < 6; j++)
        {
            if (getchar() != target[j])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            sum++;
        flag = 0;
        while (getchar() != '\n')
            ;
    }
    printf("NSDstu=%d", sum);
}