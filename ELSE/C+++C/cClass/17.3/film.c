//��д���film.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

void InitializeList(List *plist)
{
    plist->items = 0; //��������Ϊ0ʱ�൱���������
    return;
}

bool ListIsEmpty(const List *plist)
{
    return plist->items == 0 ? true : false; //�ж�list���Ƿ���Ԫ��
}

bool ListIsFull(const List *plist)
{
    return plist->items == MAXSIZE ? true : false; //�ж�list�е�Ԫ���Ƿ��Ѿ�����
}

unsigned int ListItemCount(const List *plist)
{
    return plist->items; //�ж�list�е�Ԫ�صĸ���
}

bool AddItem(Item item, List *plist)
{
    if (plist->items == MAXSIZE) //����Ŀ���ﵽ���ֵ�򲻿����;
    {
        return false;
    }
    else //��Ŀ��δ�ﵽ���ֵ���������Ŀ����Ŀ�����в������������;
    {
        plist->entries[plist->items++] = item;
        return true;
    }
}

void Traverse(const List *plist, void (*pfun)(Item item))
{
    int i;

    for (i = 0; i < plist->items; i++) //����list�е���
    {
        (*pfun)(plist->entries[i]); //ʹpunָ��ĺ�����������Ŀ�����е�ÿһ��;
    }
    return;
}

void EmptyTheList(List *plist)
{
    plist->items = 0;
    return;
}

void showmovies(Item item);
char *s_gets(char *st, int n);

int main(void)
{
    List movies;
    Item temp;

    InitializeList(&movies); //��list��ʼ��
    if (ListIsFull(&movies)) //���list����
    {
        fprintf(stderr, "No memory available! Bye!\n");
        exit(1);
    }
    puts("Enter first movie title:");
    while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0')
    {
        puts("Enter your rating <0-10>:");
        scanf("%d", &temp.rating); //�����ݴ洢��temp��
        while (getchar() != '\n')
            continue;
        if (AddItem(temp, &movies) == false) //��temp���뵽movie��
        {
            fprintf(stderr, "Problem allocating memory\n");
            break;
        }
        if (ListIsFull(&movies))
        {
            puts("The list is now full.");
            break;
        }
        puts("Enter next movie title (empty line to stop):");
    }
    if (ListIsEmpty(&movies))
    {
        printf("No data entered. ");
    }
    else
    {
        printf("Here is the movie list:\n");
        Traverse(&movies, showmovies);
    }
    printf("You entered %d movies.\n", ListItemCount(&movies));
    EmptyTheList(&movies);
    printf("Bye!\n");

    return 0;
}

void showmovies(Item item)
{
    printf("Movie: %s  Rating: %d\n", item.title,
           item.rating);
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find) //���ֻ������һ������
        {
            *find = '\0'; //���ַ�����Ϊ��
        }
        else
        {
            while (getchar() != '\n') //������
                continue;
        }
    }
    return ret_val;
}
