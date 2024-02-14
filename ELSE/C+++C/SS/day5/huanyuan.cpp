#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
} node;
int n;
char pre[MAX], in[MAX];

node *creattree(char pre[], char in[], int size)
{
    if (size == 0)
        return NULL;
    char now_root_data = pre[0];
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
    root->data = now_root_data;
    root->lchild = creattree(pre + 1, in, lsize);
    root->rchild = creattree(pre + lsize + 1, in + lsize + 1, size - lsize - 1);
    return root;
}
int deeptree(node *T)
{
    if (T == NULL)
        return 0;
    int left = deeptree(T->lchild), right = deeptree(T->rchild);
    return left > right ? left + 1 : right + 1;
}
int main()
{
    cin >> n;
    scanf("%s", pre);
    scanf("%s", in);
    node *root = new node;
    root = creattree(pre, in, n);
    cout<<deeptree(root);
}