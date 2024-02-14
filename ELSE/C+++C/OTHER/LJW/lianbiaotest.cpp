#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status; // Status 是函数返回值类型，其值是函数结果状态代码。

typedef int ElemType; // ElemType 为可定义的数据类型，此设为int类型

typedef struct LNode
{
    ElemType data;      //结点的数据域
    struct LNode *next; //结点的指针域
} LNode, *linkList;     // linkList为指向结构体LNode的指针类型

Status InitList(linkList &L)
{
    L = NULL;
    return OK;
}
Status DestroyList(linkList &L)
{
    while (L)
    {
        linkList q;
        q = L->next;
        delete L;
        L = q;
    }
    return OK;
}
int ListLength(linkList L)
{
    int len = 0;
    linkList p;
    p = L;
    while (p)
    {
        len++;
        p = p->next;
    }
    return len;
}
bool ListEmpty(linkList L)
{
    if (L == NULL)
        return true;
    return false;
}
Status GetElem(linkList L, int i, ElemType &e)
{
    linkList p;
    int j = 1;
    p = L;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
        return ERROR;
    e = p->data;
    return OK;
}
int LocateElem(linkList L, int e)
{
    linkList p;
    int i = 1;
    p = L;
    while (p && p->data != e)
    {
        i++;
        p = p->next;
    }
    if (p == NULL)
    {
        return ERROR;
    }
    else
        return i;
}
Status ListInsert(linkList &L, int i, ElemType e)
{
    linkList p, s;
    int j = 1;
    p = L;
    if (i == 1)
    {
        s = new LNode;
        s->data = e;
        s->next = L;
        L=s;
    }
    else
    {
        while (p && (j < i - 1))
        {
            p = p->next;
            ++j;
        }
        if (!p || j > i - 1)
            return ERROR;
        s = new LNode;
        s->data = e;
        s->next = p->next;
        p->next = s;
    }
    return OK;
}
Status ListDelete(linkList &L, int i)
{
    linkList p, q;
    int j = 1;
    p = L;
    if (i == 1)
    {
        L=L->next;
        delete p;
    }
    else
    {
        while (p->next && j < i - 1)
        {
            p = p->next;
            j++;
        }
        if (!(p->next) || j > i - 1)
            return ERROR;
        q = p->next;
        p->next = q->next;
        delete q;
    }
    return OK;
}
void ListPrint(linkList L)
{
    LNode *p;
    for (p = L; p; p = p->next)
        cout << p->data << (p->next ? ' ' : '\n');
}

int main()
{
    int i;
    ElemType e;
    linkList L;
    string op;
    InitList(L);
    while (cin >> op)
    {
        if (op == "Empty")
            cout << (ListEmpty(L) ? "Empty" : "Not empty") << endl;
        else if (op == "Insert")
        {
            cin >> i >> e;
            if (ListInsert(L, i, e) == ERROR)
                cout << "Insert failed" << endl;
            else
                ListPrint(L);
        }
        else if (op == "Length")
        {
            cout << "List length is " << ListLength(L) << endl;
        }
        else if (op == "GetElem")
        {
            cin >> i;
            if (GetElem(L, i, e) == ERROR)
                cout << "Out of index" << endl;
            else
                cout << "The elem at position " << i << " is " << e << endl;
        }
        else if (op == "LocateElem")
        {
            cin >> e;
            i = LocateElem(L, e);
            if (i == 0)
                cout << e << " is not found in list" << endl;
            else
                cout << e << " is found at the position " << i << endl;
        }
        else if (op == "Delete")
        {
            cin >> i;
            if (ListDelete(L, i) == ERROR)
                cout << "Delete failed" << endl;
            else
                ListPrint(L);
        }
    }
    DestroyList(L);
    return 0;
}
