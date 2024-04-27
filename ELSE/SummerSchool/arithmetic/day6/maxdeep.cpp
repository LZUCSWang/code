#include <bits/stdc++.h>
using namespace std;
#define item pair<node *, int>
typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} node;
node *creat_tree(node *root)
{
    int data;
    cin >> data;
    if (data == 0)
        return NULL;
    root = (node *)malloc(sizeof(node));
    root->data = data;
    root->lchild = creat_tree(root->lchild);
    root->rchild = creat_tree(root->rchild);
    return root;
}
queue<item> q;
int allhigh = 0;
int start_data, end_data;
void levelOrder(node *T)
{
    q.push(make_pair(T, 0));
    while (!q.empty())
    {
        item p = q.front();
        q.pop();
        T = p.first;
        int now_high = p.second;
        // printf("%d", T->data);
        if (now_high > allhigh)
        {
            allhigh = now_high;
            start_data = T->data;
        }
        if (T->lchild != NULL)
            q.push(make_pair(T->lchild, now_high + 1));
        if (T->rchild != NULL)
            q.push(make_pair(T->rchild, now_high + 1));
    }
    end_data = T->data;
    cout << fabs(start_data - end_data) << endl;
}
int main()
{
    node *T = creat_tree(T);
    levelOrder(T);
}