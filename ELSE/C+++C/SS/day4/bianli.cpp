#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
} node;
int cnt = 0;
node *creat_tree(node *root)
{
    char data;
    data = getchar();
    if (data == '#')
    {
        if (cnt == 0)
        {
            printf("0\n");
            exit(0);
        }
        return NULL;
    }
    cnt++;
    root = (node *)malloc(sizeof(node));
    root->data = data;
    root->lchild = creat_tree(root->lchild);
    root->rchild = creat_tree(root->rchild);
    return root;
}
void zhongxu(node *T)
{
    if (T == NULL)
        return;
    zhongxu(T->lchild);
    printf("%c", T->data);
    zhongxu(T->rchild);
}
void qianxu(node *T)
{
    if (T == NULL)
        return;
    printf("%c", T->data);
    qianxu(T->lchild);
    qianxu(T->rchild);
}
void houxu(node *T)
{
    if (T == NULL)
        return;
    houxu(T->lchild);
    houxu(T->rchild);
    printf("%c", T->data);
}
int count(node *T)
{
    if (T == NULL)
    {
        return 0;
    }
    if (T->lchild == NULL && T->rchild == NULL)
    {
        return 1;
    }
    int left = count(T->lchild);
    int right = count(T->rchild);
    return left + right;
}
int main()
{
    node *root = new node;
    root = creat_tree(root);
    qianxu(root);
    printf("\n");
    zhongxu(root);
    printf("\n");
    houxu(root);
    printf("\n");
    printf("%d", count(root));
    return 0;
}