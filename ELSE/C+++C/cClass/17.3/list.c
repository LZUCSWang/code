//重写后的list.c,以适应新的list结构
#include <stdio.h>
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