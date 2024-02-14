#include <bits/stdc++.h>
using namespace std;
typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} node;
void levelOrder(int fa, int lr, int son, node *T)
{
    queue<node *> q;
    q.push(T);
    while (!q.empty())
    {
        node *p;
        p = q.front();
        q.pop();
        // printf("%c", T->data);
        if (p->data == fa)
        {
            if (lr == 0)
            {
                node *now = new node;
                now->data = son;
                now->lchild = NULL;
                now->rchild = NULL;
                p->lchild = now;
            }
            else
            {
                node *now = new node;
                now->data = son;
                now->lchild = NULL;
                now->rchild = NULL;
                p->rchild = now;
            }
            break;
        }
        if (p->lchild != NULL)
            q.push(p->lchild);
        if (p->rchild != NULL)
            q.push(p->rchild);
    }
}
void zhongxu(node *T)
{
    if (T == NULL)
        return;
    zhongxu(T->lchild);
    printf("%d\n", T->data);
    zhongxu(T->rchild);
}
int n, gen;
bool flag;
void rightsearch(int fa, int lr, int son, node *T)
{
    if (T == NULL)
        return;
    if (fa == T->data)
    {
        if (lr == 0)
        {
            node *now = new node;
            now->lchild = NULL;
            now->rchild = NULL;
            now->data = son;
            T->lchild = now;
        }
        else
        {
            node *now = new node;
            now->lchild = NULL;
            now->rchild = NULL;
            now->data = son;
            T->rchild = now;
        }
    }
    else
    {
        if (fa > T->data)
        {
            rightsearch(fa, lr, son, T->rchild);
        }
        else
        {
            rightsearch(fa, lr, son, T->lchild);
        }
    }
}
void insertt(int fa, int lr, int son, node *T)
{
    if (flag)
    {
        rightsearch(fa, lr, son, T);
    }
    else
    {
        levelOrder(fa, lr, son, T);
    }
}
int main()
{
    cin >> n;
    if (n == 0)
    {
        cout << "Yes" << endl;
        return 0;
    }
    cin >> gen;
    flag = true;
    node *T = (node *)malloc(sizeof(node));
    T->data = gen;
    int fa, lr, son;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> fa >> lr >> son;
        if (flag && (lr == 1 && fa > son || lr == 0 && fa < son))
        {
            flag = false;
        }
        insertt(fa, lr, son, T);
    }
    zhongxu(T);
    if (flag)
        printf("Yes");
    else
        printf("No");
}