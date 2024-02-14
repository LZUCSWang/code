#include <stdio.h>
#include <stdio.h>
int main(void)
{
    int i = 0, j = 0;
    char *l[10][11];
    for (i = 0; i <= 9; i++)
    {
        for (j = 0; j <= 10; j++)
        {
            l[i][j] = (char *)malloc(sizeof(char) * 2);
            strcpy(l[i][j], "0");
        }
    }
    l[0][2] = "��";
    l[0][4] = "��";
    l[0][6] = "��";
    l[0][8] = "��";
    l[1][0] = "ǧ";
    l[3][0] = "��";
    l[5][0] = "ӭ";
    l[7][0] = "��";
    l[9][0] = "��";
    l[1][10] = "��";
    l[3][10] = "ѩ";
    l[5][10] = "��";
    l[7][10] = "��";
    l[9][10] = "��";
    for (i = 0; i <= 9; i++)
    {
        for (j = 0; j <= 10; j++)
        {
            if (strcmp(l[i][j], "0") == 0)
            {
                putchar(32);
            }
            else
                printf("%s", l[i][j]);
        }
        putchar(10);
    }
}
