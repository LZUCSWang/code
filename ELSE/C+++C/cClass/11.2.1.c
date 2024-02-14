#include <stdio.h>
int main()
{
    FILE *fp;
    int datas[10] = {1, 2, 3}, i, n;
    fp = fopen("dl.txt", "w");
    for (i = 0; i < 3; i++)
        fprintf(fp, "%d", datas[i]);
    fprintf(fp, "\n");
    fclose(fp);
    fp = fopen("dl.txt", "r");
    fscanf(fp, "%d", &n);
    fclose(fp);
    printf("%d\n", n);
    return 0;
}