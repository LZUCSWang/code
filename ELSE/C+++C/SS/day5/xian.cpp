#include <bits/stdc++.h>
using namespace std;
typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
} node;
queue<node *> q;
node *creat_tree(node *root)
{
    char data;
    data = getchar();
    if (data == '#')
        return NULL;
    root = (node *)malloc(sizeof(node));
    root->data = data;
    root->lchild = creat_tree(root->lchild);
    root->rchild = creat_tree(root->rchild);
    return root;
}
void levelOrder(node *T)
{
    while (T != NULL)
    {
        printf("%c", T->data);
        if (T->lchild != NULL)
            // queue[rear++] = T->lchild;
            q.push(T->lchild);
        if (T->rchild != NULL)
            // queue[rear++] = T->rchild;
            q.push(T->rchild);
        // if (front + 1 == rear)
        //     break;
        if (q.empty())
            break;
        // T = queue[++front];
        T = q.front();
        q.pop();
    }   
}
int main()
{
    node *nt;
    nt = creat_tree(nt);
    levelOrder(nt);
}