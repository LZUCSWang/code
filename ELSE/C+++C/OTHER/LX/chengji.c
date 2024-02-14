#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stu
{
    char name[20];
    int id;
    int chi;
    int eng;
    int math;
    struct stu *next;
    /* data */
} stu;
//插入学生信息
void insert(stu **head)
{
    stu *p = (*head)->next;
    stu *q = (stu *)malloc(sizeof(stu));
    printf("Enter stu name:");
    scanf("%s", q->name);
    printf("Enter stu id:");
    scanf("%d", &q->id);
    printf("Enter chi score:");
    scanf("%d", &q->chi);
    printf("Enter eng score:");
    scanf("%d", &q->eng);
    printf("Enter math score:");
    scanf("%d", &q->math);
    q->next = NULL;
    if ((*head)->next == NULL)
    {
        (*head)->next = q;
    }
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = q;
    }
}
//删除学生信息
void delete (stu **head)
{
    stu *p = (*head)->next;
    stu *q = (*head)->next;
    char name[20];
    printf("Enter the stu name:");
    scanf("%s", name);
    if ((*head)->next == NULL)
    {
        printf("Empty!");
    }
    else
    {
        if (strcmp(p->name, name) == 0)
        {
            (*head)->next = p->next;
            free(p);
        }
        else
        {
            while (p->next != NULL)
            {
                if (strcmp(p->next->name, name) == 0)
                {
                    q->next = p->next->next;
                    free(p->next);
                    break;
                }
                q = p;
                p = p->next;
            }
        }
    }
}
//查找学生信息
void search(stu **head)
{
    stu *p = (*head)->next;
    char name[20];
    printf("Enter the name:");
    scanf("%s", name);
    if (p == NULL)
    {
        printf("Empty!");
    }
    else
    {
        while (p != NULL)
        {
            if (strcmp(p->name, name) == 0)
            {
                printf("Name:%s\n", p->name);
                printf("ID:%d\n", p->id);
                printf("Chinese:%d\n", p->chi);
                printf("English:%d\n", p->eng);
                printf("Math:%d\n", p->math);
                printf("total:%d\n", p->chi + p->eng + p->math);
                break;
            }
            p = p->next;
        }
    }
}
//展示学生信息
void display(stu **head)
{
    stu *p = (*head)->next;
    if ((*head)->next == NULL)
    {
        printf("Empty!\n");
    }
    else
    {
        printf("Name Id  Chinese  English  Math  Total\n");
        while (p != NULL)
        {
            printf("%4s", p->name);
            printf("%4d", p->id);
            printf("%4d", p->chi);
            printf("%4d", p->eng);
            printf("%4d", p->math);
            printf("%4d\n", p->chi + p->eng + p->math);
            p = p->next;
        }
    }
}
//菜单
void menu(stu *head)
{
    printf("Enter your choice:\n");
    printf("1.Insert\n");
    printf("2.Delete\n");
    printf("3.Search\n");
    printf("4.Display\n");
    printf("5.Exit\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        insert(&head);
        break;
    case 2:
        delete (&head);
        break;
    case 3:
        search(&head);
        break;
    case 4:
        display(&head);
        break;
    case 5:
        exit(0);
    }
}

int main()
{
    stu *head = (stu *)malloc(sizeof(stu));
    head->next = NULL;
    while (1)
    {
        menu(head);
    }
}