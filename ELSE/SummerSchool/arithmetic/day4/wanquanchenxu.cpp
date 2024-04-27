#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} node; 
int maxhigh, cnt, n, max_wai_node;
void yu()
{
    int s = 0, i;
    for (i = 0; i <= 10000 && s < n; i++)
    {
        s += pow(2, i);
    }
    maxhigh = i - 1;
    max_wai_node = n - s + pow(2, i - 1);
}
node *creat_tree(node *root, int high)
{
    if (high == maxhigh + 1)
    {
        return NULL;
    }
    if (high == maxhigh && cnt == max_wai_node)
    {
        return NULL;
    }
    root->lchild = (node *)malloc(sizeof(node));
    root->lchild = creat_tree(root->lchild, high + 1);
    root->rchild = (node *)malloc(sizeof(node));
    root->rchild = creat_tree(root->rchild, high + 1);
    if (high == maxhigh)
    {
        cnt++;
    }
    int data;
    cin >> data;
    root->data = data;
    return root;
}
void levelOrder(node *T)
{
    node *queue[100000];
    int front = 0, rear = 1;
    while (T != NULL)
    {
        cnt++;
        printf("%d", T->data);
        if (cnt != n)
            printf(" ");
        if (T->lchild != NULL)
            queue[rear++] = T->lchild;
        if (T->rchild != NULL)
            queue[rear++] = T->rchild;
        if (front + 1 == rear)
            break;
        T = queue[++front];
    }
}
int main()
{
    cin >> n;
    yu();
    node *T = (node *)malloc(sizeof(node));
    T = creat_tree(T, 0);
    cnt = 0;
    levelOrder(T);
}