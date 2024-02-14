// #include "stdafx.h"
#include <stdio.h>
#include "iostream"
using namespace std;
#include <stdlib.h>
#define ElemType char
#define NodeNum 100
typedef struct BTNode
{
    ElemType data;         // 结点数据
    struct BTNode *lchild; // 左子结点指针
    struct BTNode *rchild; // 右子结点指针
} BTNode, *BinTree;
void VISIT(char e) // 输出语句
{
    printf("%c", e);
}
BTNode *Create_BTree(BinTree &T) // 建立链式二叉树，返回指向根结点的指针变量
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
void PREORDER(BinTree T) // 二叉树的前序遍历
{
    if (T != NULL)
    {
        VISIT(T->data);
        PREORDER(T->lchild);
        PREORDER(T->rchild);
    }
}
void INORDER(BinTree T) // 二叉树的中序遍历
{
    if (T != NULL)
    {
        INORDER(T->lchild);
        VISIT(T->data);
        INORDER(T->rchild);
    }
}
void POSTORDER(BinTree T) // 二叉树的后序遍历
{
    if (T != NULL)
    {
        POSTORDER(T->lchild);
        POSTORDER(T->rchild);
        VISIT(T->data);
    }
}
void AllPath(BinTree T, char item) //-----求指定路径结点
{
    BinTree STACK1[NodeNum], p = T;
    int tag[NodeNum];
    int top = 0, flag;                //----定义一个堆栈，保存所找到的结点
    if (T != NULL && T->data != item) //-----假如所找的结点不是根结点
        do
        {
            while (p != NULL)
            {
                STACK1[++top] = p;
                tag[top] = 0;
                p = p->lchild;
            } // 扫描左子树
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
        } while (!(p == NULL && top == 0)); //------通过后序遍历非递归算法循环语句实现查找
}

int menuselect() // 主菜单显示
{
    int sn;
    cout << endl;
    cout << "===========二叉树结点路径=============" << endl;
    cout << "        1  建立二叉树                 " << endl;
    cout << "        2 前序遍历输出二叉树                  " << endl;
    cout << "        3 中序遍历输出二叉树                  " << endl;
    cout << "        4 后序遍历输出二叉树                  " << endl;
    cout << "        5 求给定结点路径                " << endl;
    cout << "        0 退出                          " << endl;
    cout << "=========================================";
    cout << endl;
    for (;;)
    {
        cin >> sn;
        if (sn < 0 || sn > 5)
            cout << "输入错误，请重新输入" << endl;
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
            cout << "  建立一个二叉树：  " << endl;
            T = Create_BTree(T);
            getchar();
            break;
        case 2:
            cout << "  前序遍历输出二叉树为：  " << endl;
            PREORDER(T);
            break;
        case 3:
            cout << "  中序遍历输出二叉树为：  " << endl;
            INORDER(T);
            break;
        case 4:
            cout << "  后序遍历输出二叉树为：  " << endl;
            POSTORDER(T);
            break;
        case 5:
            cout << "  求给定结点路径：  " << endl;
            {
                cout << "请输入要查找的结点：";
                cin >> item;
                AllPath(T, item);
                break;
            }
        case 0:
            cout << " 退出  " << endl;
            flag = 0;
            break;
        }
    }
    return 0;
}
