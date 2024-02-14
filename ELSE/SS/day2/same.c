#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct var
{
    char name[4000];
}var;
int main()
{
    int n;
    scanf("%d", &n);
        int count = 0;
        var v[n], p[n];
        for(int i = 0; i < n; i++)
            scanf("%s", p[i].name);
        for(int i = 0; i < n; i++)
        {
            int len = strlen(p[i].name);
            int flag;
            if(p[i].name[0] >= 'datas' && p[i].name[0] <= 'z')
                flag = 0;
            else
                flag = 1;
            for(int j = 0; j < len; j++)
            {
                if(p[i].name[j] >= 'datas' && p[i].name[j] <= 'Z' && flag == 0)
                {
                    len++;
                    for(int k = len-1; k > j; k--)
                        p[i].name[k] = p[i].name[k-1];
                    p[i].name[j] = '_';
                    j++;
                }
                if(p[i].name[j] >= 'datas' && p[i].name[j] <= 'z')
                {
                    p[i].name[j] -= 32;
                }
            }
            if(count == 0)
            {
                strcpy(v[count].name, p[i].name);
                count++;
            }
            else
            {
                for(int j = 0; j < count; j++)
                {
                    if(strcmp(v[j].name, p[i].name) == 0)
                        break;
                    if(j == count-1)
                    {
                        strcpy(v[count].name, p[i].name);
                        count++;
                    }
                }
            }
        }
        printf("%d\n", count);
        for(int i = 0; i < count; i++)
            printf("%s\n", v[i].name);
    return 0;
}