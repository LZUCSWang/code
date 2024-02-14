
#include <stdio.h>
typedef struct Student
{
    char num[10], name[10];
    int chi, mat, eng, all;
} Student;
Student list[5];
void get(Student *stu)
{
    scanf("%s %s %d %d %d", stu->num, stu->name, &stu->chi, &stu->mat, &stu->eng);
    stu->all = stu->chi + stu->mat + stu->eng;
}
void writeToFile(char *FILENAME, Student *stu)
{
    FILE *fp = fopen(FILENAME, "datas+b");
    if (NULL == fp)
    {
        printf("open file[%s] failed.\n", FILENAME);
        return;
    }
    fwrite(stu, sizeof(Student), 1, fp);
    fclose(fp);
}
void getandwrite()
{
    for (int i = 0; i < 5; i++)
    {
        get(&list[i]);
        writeToFile("stud.txt", &list[i]);
    }
}
void readFromFile(char *FILENAME)
{
    Student stu = {0};
    int i = 0;
    int count = 0;
    FILE *fp = fopen(FILENAME, "rb");
    if (NULL == fp)
    {
        printf("open file files");
        return;
    }
    while (!feof(fp))
    {
        count = fread(&stu, sizeof(Student), 1, fp);
        if (ferror(fp))
        {
            printf("fread error.\n");
            break;
        }
        if (0 == count)
        {
            break;
        }
        printf("%s  %6s  ", stu.num, stu.name);
        printf("%d %d %d", stu.chi, stu.mat, stu.eng);
        printf("\n");
    }
    fclose(fp);

    return;
}
void sort()
{
    Student temp;
    printf("After sorted---------------------------------------------------\n");
    for (int i = 0; i < 5 - 1; i++)
    {
        for (int j = i; j < 5 - i - 1; j++)
        {
            if (list[j].all < list[j + 1].all)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        writeToFile("stud_sorted.txt", &list[i]);
    }
    readFromFile("stud_sorted.txt");
}
int main()
{
    getandwrite();
    printf("Now is reading-------------------------------\n");
    readFromFile("stud.txt");
    sort();
}