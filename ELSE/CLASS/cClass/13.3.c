#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char file[100];
    char ch;
    FILE *fp;
    puts("Please enter file name :");
    scanf("%s", file);
    if ((fp = fopen(file, "r+")) == NULL)
    {
        printf("Can't open the %s\n", file);
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        if (islower(ch))
        {
            fseek(fp, -1, SEEK_CUR);
            putc(toupper(ch), fp);
            fseek(fp, 0, SEEK_CUR);
        }
    }
    if (fclose(fp) != 0)
        printf("Error in closing files.\n");
    return 0;
}