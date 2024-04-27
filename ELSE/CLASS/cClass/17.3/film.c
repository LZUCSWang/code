//重写后的film.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

void InitializeList(List *plist)
{
    plist->items = 0; //将项数置为0时相当于清空数组
    return;
}

bool ListIsEmpty(const List *plist)
{
    return plist->items == 0 ? true : false; //判断list中是否有元素
}

bool ListIsFull(const List *plist)
{
    return plist->items == MAXSIZE ? true : false; //判断list中的元素是否已经满了
}

unsigned int ListItemCount(const List *plist)
{
    return plist->items; //判断list中的元素的个数
}

bool AddItem(Item item, List *plist)
{
    if (plist->items == MAXSIZE) //若项目数达到最大值则不可添加;
    {
        return false;
    }
    else //项目数未达到最大值则添加新项目到项目数组中并更新项的数量;
    {
        plist->entries[plist->items++] = item;
        return true;
    }
}

void Traverse(const List *plist, void (*pfun)(Item item))
{
    int i;

    for (i = 0; i < plist->items; i++) //遍历list中的项
    {
        (*pfun)(plist->entries[i]); //使pun指向的函数作用于项目数组中的每一项;
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

    InitializeList(&movies); //将list初始化
    if (ListIsFull(&movies)) //如果list已满
    {
        fprintf(stderr, "No memory available! Bye!\n");
        exit(1);
    }
    puts("Enter first movie title:");
    while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0')
    {
        puts("Enter your rating <0-10>:");
        scanf("%d", &temp.rating); //将数据存储到temp中
        while (getchar() != '\n')
            continue;
        if (AddItem(temp, &movies) == false) //将temp加入到movie中
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
        if (find) //如果只输入了一个换行
        {
            *find = '\0'; //将字符串置为空
        }
        else
        {
            while (getchar() != '\n') //清理行
                continue;
        }
    }
    return ret_val;
}
