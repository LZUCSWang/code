#include <bits/stdc++.h>
using namespace std;
typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
} node;
int cnt = 0, cnt_active = 0, cnt_active_now = 0;
queue<node *> q;
node *creat_tree(node *root, int n_node)
{
    int data;
    scanf("%d", &data);
    cnt_active = 1;
    root = (node *)malloc(sizeof(node));
    root->data = data;
    cnt++;
    q.push(root);
    while (q.empty() == false)
    {
        node *roots = q.front();
        q.pop();
        if (cnt != n_node)
        {
            scanf("%d", &data);
            if (data)
                cnt_active++;
            roots->lchild = (node *)malloc(sizeof(node));
            (roots->lchild)->data = data;
            q.push(roots->lchild);
            cnt++;
        }
        else
        {
            roots->lchild = NULL;
            roots->rchild = NULL;
        }
        if (cnt != n_node)
        {

            scanf("%d", &data);
            if (data)
                cnt_active++;
            roots->rchild = (node *)malloc(sizeof(node));
            (roots->rchild)->data = data;
            q.push(roots->rchild);
            cnt++;
        }
        else
        {
            roots->rchild = NULL;
        }
    }
    return root;
}
void zhongxu(node *T)
{
    if (T == NULL)
        return;
    zhongxu(T->lchild);
    if (T->data)
    {
        cnt_active_now++;
        printf("%d", T->data);
        if (cnt_active_now != cnt_active)
        {
            printf(" ");
        }
    }
    zhongxu(T->rchild);
}
int deeptree(node *T)
{
    if (T == NULL || T->data == 0)
        return 0;
    int left = deeptree(T->lchild), right = deeptree(T->rchild);
    return left > right ? left + 1 : right + 1;
}
void main_work()
{
    int n_node;
    cin >> n_node;
    node *head;
    cnt_active_now = 0;
    head = creat_tree(head, n_node);
    zhongxu(head);
    printf("\n");
    printf("%d\n", deeptree(head));
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++, cnt = 0)
    {
        main_work();
    }
}