#include <bits/stdc++.h>
using namespace std;
#define MAX 1000005
char input[MAX];
int pos = 0;
typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
} node;
node *creat_tree(node *root)
{
    char data;
    data = input[pos++];
    if (data == '*')
        return NULL;
    root = (node *)malloc(sizeof(node));
    root->data = data;
    root->lchild = creat_tree(root->lchild);
    root->rchild = creat_tree(root->rchild);
    return root;
}
int ans = 0;
void qianxu(node *T)
{
    if (T == NULL)
        return;
    if (T->lchild == NULL && T->rchild || T->lchild && T->rchild == NULL)
    {
        ans++;
    }
    qianxu(T->lchild);
    qianxu(T->rchild);
}
int main()
{
    while (scanf("%s", input) != EOF)
    {
        pos = 0;
        ans = 0;
        node *T = creat_tree(T);
        qianxu(T);
        cout << "num: " << ans << endl;
    }
}