#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status; // Status 是函数返回值类型，其值是函数结果状态代码。

typedef int ElemType; // ElemType 为可定义的数据类型，此设为int类型

#define MAXSIZE 100 //链表可能达到的最大长度

typedef struct LNode
{
   ElemType data;      //结点的数据域
   struct LNode *next; //结点的指针域
} LNode, *LinkList;    // linkList为指向结构体LNode的指针类型

Status InitList(LinkList &L) //算法2.6 单链表的初始化
{
   //构造一个空的单链表L
   L = new LNode;  //生成新结点作为头结点，用头指针L指向头结点
   L->next = NULL; //头结点的指针域置空
   return OK;
}

Status DestroyList(LinkList &L)
{
   /* 初始条件：线性表L已存在。操作结果：销毁线性表L */
   LinkList q;
   while (L)
   {
      q = L->next;
      delete L;
      L = q;
   }
   return OK;
}

int ListLength(LinkList L)
{
   /****在此下面完成代码***************/
   int len = 0;
   LinkList p;
   p = L->next;
   while (p != NULL)
   {
      len++;
      p = p->next;
   }
   return len;
   /***********************************/
}

bool ListEmpty(LinkList L)
{
   /****在此下面完成代码***************/
   if (L->next == NULL)
      return true;
   return false;
   /***********************************/
}

Status GetElem(LinkList L, int i, ElemType &e) //算法2.7 单链表的取值
{
   /****在此下面完成代码***************/
   LinkList p;
   int j = 1;
   p = L->next;
   while (p && j < i)
   {
      p = p->next;
      j++;
   }
   if (!p || j > i)
      return ERROR;
   e = p->data;
   return OK;
   /***********************************/
} // GetElem

int LocateElem(LinkList L, int e) //略有改动 算法2.8 按值查找
{
   /****在此下面完成代码***************/
   LinkList p;
   p = L->next;
   while (p && p->data != e)
      p = p->next;
   if (p == NULL)
   {
      return ERROR;
   }
   return p->data;
   /*************************************/
} // LocateElem

Status ListInsert(LinkList &L, int i, ElemType e) //算法2.9 单链表的插入
{
   /****在此下面完成代码***************/
   LinkList p, s;
   int j = 0;
   p = L;
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
   return OK;
   /***********************************/
} // ListInsert

Status ListDelete(LinkList &L, int i) //算法2.10 单链表的删除
{
   /****在此下面完成代码***************/
   LinkList p, q;
   int j = 0;
   p = L;
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
   return OK;
}
/***********************************/
// ListDelete

void ListPrint(LinkList L)
{
   LNode *p;
   for (p = L->next; p; p = p->next)
      cout << p->data << (p->next ? ' ' : '\n');
}

int main()
{
   int i;
   ElemType e;
   LinkList L;
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
