// #include "stdafx.h"
#include <stdio.h>
#include "iostream"
using namespace std;
#include <stdlib.h>
#define ElemType char
#define NodeNum 100
typedef struct BTNode
{
    ElemType data;         // �������
    struct BTNode *lchild; // ���ӽ��ָ��
    struct BTNode *rchild; // ���ӽ��ָ��
} BTNode, *BinTree;
void VISIT(char e) // ������
{
    printf("%c", e);
}
BTNode *Create_BTree(BinTree &T) // ������ʽ������������ָ�������ָ�����
{
    ElemType ch;
    ch = getchar();
    // getchar();
    if (ch == '?')
    {
        T = NULL;
        return (T);
    }
    else
    {
        T = (BTNode *)malloc(sizeof(BTNode));
        T->data = ch;
        Create_BTree(T->lchild);
        Create_BTree(T->rchild);
        return (T);
    }
}
void PREORDER(BinTree T) // ��������ǰ�����
{
    if (T != NULL)
    {
        VISIT(T->data);
        PREORDER(T->lchild);
        PREORDER(T->rchild);
    }
}
void INORDER(BinTree T) // ���������������
{
    if (T != NULL)
    {
        INORDER(T->lchild);
        VISIT(T->data);
        INORDER(T->rchild);
    }
}
void POSTORDER(BinTree T) // �������ĺ������
{
    if (T != NULL)
    {
        POSTORDER(T->lchild);
        POSTORDER(T->rchild);
        VISIT(T->data);
    }
}
void AllPath(BinTree T, char item) //-----��ָ��·�����
{
    BinTree STACK1[NodeNum], p = T;
    int tag[NodeNum];
    int top = 0, flag;                //----����һ����ջ���������ҵ��Ľ��
    if (T != NULL && T->data != item) //-----�������ҵĽ�㲻�Ǹ����
        do
        {
            while (p != NULL)
            {
                STACK1[++top] = p;
                tag[top] = 0;
                p = p->lchild;
            } // ɨ��������
            p = STACK1[top];
            flag = tag[top--];
            if (flag == 0)
            {
                STACK1[++top] = p;
                tag[top] = 1;
                p = p->rchild;
            }
            else
            {
                if (p->data == item)
                {
                    while (top != 0)
                    {
                        cout << STACK1[top--]->data;
                    }

                    break;
                }
                else
                    p = NULL;
            }
        } while (!(p == NULL && top == 0)); //------ͨ����������ǵݹ��㷨ѭ�����ʵ�ֲ���
}

int menuselect() // ���˵���ʾ
{
    int sn;
    cout << endl;
    cout << "===========���������·��=============" << endl;
    cout << "        1  ����������                 " << endl;
    cout << "        2 ǰ��������������                  " << endl;
    cout << "        3 ����������������                  " << endl;
    cout << "        4 ����������������                  " << endl;
    cout << "        5 ��������·��                " << endl;
    cout << "        0 �˳�                          " << endl;
    cout << "=========================================";
    cout << endl;
    for (;;)
    {
        cin >> sn;
        if (sn < 0 || sn > 5)
            cout << "�����������������" << endl;
        else
            break;
    }
    getchar();
    return sn;
}
int main()
{
    BTNode *T;
    char item;
    int flag = 1;
    while (flag)
    {
        switch (menuselect())
        {
        case 1:
            cout << "  ����һ����������  " << endl;
            T = Create_BTree(T);
            getchar();
            break;
        case 2:
            cout << "  ǰ��������������Ϊ��  " << endl;
            PREORDER(T);
            break;
        case 3:
            cout << "  ����������������Ϊ��  " << endl;
            INORDER(T);
            break;
        case 4:
            cout << "  ����������������Ϊ��  " << endl;
            POSTORDER(T);
            break;
        case 5:
            cout << "  ��������·����  " << endl;
            {
                cout << "������Ҫ���ҵĽ�㣺";
                cin >> item;
                AllPath(T, item);
                break;
            }
        case 0:
            cout << " �˳�  " << endl;
            flag = 0;
            break;
        }
    }
    return 0;
}
