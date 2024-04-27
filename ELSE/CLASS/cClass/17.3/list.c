//��д���list.c,����Ӧ�µ�list�ṹ
#include <stdio.h>
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