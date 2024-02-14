#include <stdio.h>
#define MAX 100
int main()
{
    char name[MAX],id[MAX];
    float C, M, E, A;
    printf("Student Number\n");
    printf("Please input name:\n");
    gets(name);
    printf("Please input ID:\n");
    gets(id);//因为id可能是0开头的数字，所以用字符串表示；
    printf("Please input C, M, E:\n");
    scanf("%f,%f,%f",&C,&M,&E);
    A = (C + M + E) / 3.0;
    printf("Name:%s,id:%s,C:%.2f,M:%.2f,E:%.2f,Average:%.2f\n", name, id, C, M, E, A);
    return 0;
}
