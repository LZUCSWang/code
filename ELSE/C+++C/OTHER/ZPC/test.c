#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Student
{
    char name[10];
    char ID[10];
    int scores[3];
    double average;
    struct Student *next;
} stu;
void chuang();
void write(char *FILENAME, stu *stu);
double aver(stu *);
stu *appnode(stu *);
stu *start(stu *);
stu *insertnode(stu *);
stu *deletenode(stu *);
void sort1(stu datas[10], int m);
void shownode(stu *head);
void freememory(stu *head);
void savedata(stu *head);
int main()
{
    int datas, k = 1;
    stu *head = NULL;
    if (head == NULL)
        head = start(head);
    while (k)
    {
        shownode(head);
        printf("1.��������  2.��������  3.ɾ������\n");
        printf("4.��������  5.��ʾ����  6.�˳� 7.��ȡ���򲢱���\n");
        printf("ѡ��:");
        scanf("%d", &datas);
        getchar();
        switch (datas)
        {
        case 1:
            head = appnode(head);
            break;
        case 2:
            head = insertnode(head);
            break;
        case 3:
            head = deletenode(head);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            k = 0;
            break;
        case 7:
            chuang(head);
            k = 0;
            break;
        default:
            printf("��������Чѡ��:");
        }
    }
    freememory(head);
    system("pause");
    return 0;
}
stu *start(stu *head)
{
    stu *p = NULL;
    stu *pr = head;
    p = (stu *)malloc(sizeof(stu));
    head = p;
    pr = p;
    strcpy(pr->ID, "20210001");
    strcpy(pr->name, "Alice");
    pr->scores[0] = 97;
    pr->scores[1] = 98;
    pr->scores[2] = 99;
    pr->average = aver(pr);

    p = (stu *)malloc(sizeof(stu));
    pr->next = p;
    pr = p;
    strcpy(pr->ID, "20210002");
    strcpy(pr->name, "Bob");
    pr->scores[0] = 87;
    pr->scores[1] = 88;
    pr->scores[2] = 79;
    pr->average = aver(pr);

    p = (stu *)malloc(sizeof(stu));
    pr->next = p;
    pr = p;
    strcpy(pr->ID, "20210003");
    strcpy(pr->name, "Cile");
    pr->scores[0] = 83;
    pr->scores[1] = 98;
    pr->scores[2] = 99;
    pr->average = aver(pr);

    pr->next = NULL;
    savedata(head);
    return head;
}
stu *appnode(stu *head)
{
    stu *p = NULL;
    stu *pr = head;
    char ID[10];
    char name[10];
    int scores1;
    int scores2;
    int scores3;
    double average;
    p = (stu *)malloc(sizeof(stu));
    if (p == NULL)
    {
        printf("no memory");
        exit(1);
    }
    if (head == NULL)
    {
        head = p;
    }
    else
    {
        while ((pr->next) != NULL)
        {
            pr = pr->next;
        }
        pr->next = p;
    }
    pr = p;
    printf("please enter the school ID:");
    scanf("%s", ID);
    getchar();
    printf("enter the name:");
    scanf("%s", name);
    getchar();
    printf("enter the scores:");
    scanf("%d %d %d", &scores1, &scores2, &scores3);
    getchar();
    strcpy(pr->name, name);
    strcpy(pr->ID, ID);
    (pr->scores[0] = scores1);
    (pr->scores[1] = scores2);
    (pr->scores[2] = scores3);
    average = aver(pr);
    pr->next = NULL;
    return head;
}
stu *insertnode(stu *head)
{
    stu *p = head, *pr = head, *temp = NULL;
    int i, j;
    char ID[10];
    char name[10];
    int scores1;
    int scores2;
    int scores3;
    p = (stu *)malloc(sizeof(stu));
    printf("please enter the school ID:");
    scanf("%s", ID);
    getchar();
    printf("enter the name:");
    scanf("%s", name);
    getchar();
    printf("enter the scores:");
    scanf("%d %d %d", &scores1, &scores2, &scores3);
    getchar();
    strcpy(p->name, name);
    strcpy(p->ID, ID);
    (p->scores[0] = scores1);
    (p->scores[1] = scores2);
    (p->scores[2] = scores3);
    p->next = NULL;
    printf("please choose the location of inserting:");
    scanf("%d", &j);
    for (i = 1; i < j; i++)
    {
        temp = pr;
        pr = pr->next;
    }
    if (pr == head)
    {
        p->next = head;
        head = p;
    }
    else
    {
        pr = temp;
        p->next = pr->next;
        pr->next = p;
    }

    return head;
}
stu *deletenode(stu *head)
{
    stu *p = head, *pr = head;
    int i, j;
    printf("ɾ���ڼ�������:");
    scanf("%d", &j);
    for (i = 1; i < j; i++)
    {
        pr = p;
        p = p->next;
    }
    if (p == head)
        head = p->next;
    else
        pr->next = p->next;
    free(p);
    return head;
}
void sort1(stu datas[], int size)
{
    stu temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (datas[j].average > datas[j + 1].average)
            {
                temp = datas[j];
                datas[j] = datas[j + 1];
                datas[j + 1] = temp;
            }
        }
    }
}
void shownode(stu *head)
{
    stu *p = head;
    int j = 1;
    printf("���  ѧ��       ����   ���� ��ѧ Ӣ�� ƽ����\n");
    while (p != NULL)
    {
        printf("%d   %10s %7s  %3d  %3d  %3d  %3.2lf\n", j, p->ID, p->name,
               p->scores[0], p->scores[1], p->scores[2], p->average);
        p = p->next;
        j++;
    }
}
void freememory(stu *head)
{
    stu *p = head, *pr = NULL;
    while (p != NULL)
    {
        pr = p;
        p = p->next;
        free(pr);
    }
}
void savedata(stu *head)
{
    FILE *fp;
    fp = fopen("stud.dat", "wb");
    stu *p = head;
    int flag = 0;
    if (fp == NULL)
    {
        printf("�洢ʧ��!");
        return;
    }
    while (p != NULL)
    {
        /*fprintf(fp,"%s %s %d %d %d\n",p->ID,p->name,p->scores[0],
        p->scores[1],p->scores[2]);
        p = p->next;*/
        flag = 1;
        fwrite(p, sizeof(p), 1, fp);
        p = p->next;
    }
    fclose(fp);
    printf("����ɹ�!");
}
double aver(stu *p)
{
    double average, total = 0;
    for (int i = 0; i < 3; i++)
    {
        total += p->scores[i];
    }
    average = total / 3;
    return average;
}
void chuang(stu *head)
{
    int i = 0, count = 0;
    FILE *fp;
    stu list[10];
    stu *p = head;
    for (int j = 0; j < 3; j++)
    {
        list[j] = *p;
        p = p->next;
    }
    for (int k = 0; k < 3; k++)
    {
        write("stud_sort1.dat", &list[k]);
    }
    sort1(list, 3);
    for (int j = 0; j < 3; j++)
    {
        printf("%d   %10s %7s  %3d  %3d  %3d  %3.2lf\n", j, list[j].ID, list[j].name,
               list[j].scores[0], list[j].scores[1], list[j].scores[2], list[j].average);
    }
    fclose(fp);
}
void write(char *FILENAME, stu *stu)
{
    FILE *fp = fopen(FILENAME, "datas+b");
    if (NULL == fp)
    {
        printf("open file[%s] failed.\n", FILENAME);
        return;
    }
    fwrite(stu, sizeof(stu), 1, fp);
    fclose(fp);
}