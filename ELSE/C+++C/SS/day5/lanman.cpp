#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} node;
node *creattree(int pre[], int endpre, int in[], int size)
{
    if (size == 0)
        return NULL;
    int now_root_data = pre[endpre];
    int lsize = -1;
    node *root = new node;
    for (int i = 0; i < size; i++)
    {
        if (in[i] == now_root_data)
        {
            lsize = i;
            break;
        }
    }
    int rsize = size - lsize - 1;
    root->data = now_root_data;
    root->lchild = creattree(pre, endpre - rsize - 1, in, lsize);
    root->rchild = creattree(pre, endpre - 1, in + lsize + 1, size - lsize - 1);
    return root;
}
void qianxu(node *T)
{
    if (T == NULL)
        return;
    printf("%d", T->data);
    qianxu(T->lchild);
    qianxu(T->rchild);
}
int n, allhigh = 0;
queue<pair<node *, int>> q;
vector<int> leftans, rightans;
void levelOrder(node *T, int high)
{
    q.push(make_pair(T, high));
    int save = T->data;
    leftans.push_back(save);
    while (q.size() != 0)
    {
        pair<node *, int> now = q.front();
        q.pop();
        if (now.second == allhigh + 1)
        {
            allhigh = now.second;
            // printf("%d", now.first->data);
            leftans.push_back(now.first->data);
            rightans.push_back(save);
        }
        save = now.first->data;
        // printf("%d", now.first->data);
        if (now.first->lchild != NULL)
        {
            q.push(make_pair(now.first->lchild, now.second + 1));
        }
        if (now.first->rchild != NULL)
        {
            q.push(make_pair(now.first->rchild, now.second + 1));
        }
    }
    rightans.push_back(save);
}
int pre[MAX], in[MAX];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> in[i];
    for (int i = 0; i < n; i++)
        cin >> pre[i];
    node *root = new node;
    int high = 0;
    root = creattree(pre, n - 1, in, n);
    levelOrder(root, high);
    cout << "R: ";
    for (int i = 0; i < rightans.size(); i++)
    {
        printf("%d", rightans[i]);
        if (i != rightans.size() - 1)
            printf(" ");
    }
    printf("\nL: ");
    for (int i = 0; i < leftans.size(); i++)
    {
        printf("%d", leftans[i]);
        if (i != leftans.size() - 1)
            printf(" ");
    }
    return 0;
}