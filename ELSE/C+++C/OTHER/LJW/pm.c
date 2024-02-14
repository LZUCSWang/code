#include <stdio.h>
typedef struct data
{
    char date[11];
    int num;
} data;
int main()
{
    data list[31];
    int i = 0, j = 0;
    while (scanf("%s %d", list[i].date, &list[i].num) != EOF)
    {
        if (list[i].num < list[j].num)
            j = i;
        i++;
    }
    for(i=0;i<31;i++){
        if(list[i].num==list[j].num)printf("%s\n",list[i].date);
    }
}