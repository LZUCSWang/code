#include <bits/stdc++.h>
using namespace std;
#define item pair<node *, int>
#define MIN -2147483648
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
int all_high = 0;
int now_level_cnt = 0, ans = 0, max_sum_cnt = MIN;
void levelOrder(node *T)
{
    q.push(make_pair(T, 0));
    while (!q.empty())
    {
        item p = q.front();
        q.pop();
        T = p.first;
        int now_high = p.second;
        if (now_high > all_high)
        {
            if (now_level_cnt >= max_sum_cnt)
            {
                if (all_high != 0)
                    max_sum_cnt = now_level_cnt;
                ans = all_high;
            }
            all_high = now_high;
            now_level_cnt = 0;
        }
        if (T->lchild == NULL && T->rchild == NULL)
        {
            now_level_cnt += T->data;
        }
        if (T->lchild != NULL)
            q.push(make_pair(T->lchild, now_high + 1));
        if (T->rchild != NULL)
            q.push(make_pair(T->rchild, now_high + 1));
    }
    if (now_level_cnt >= max_sum_cnt)
    {
        ans = all_high;
    }
    cout << ans << endl;
}
int main()
{
    node *T = creat_tree(T);
    levelOrder(T);
}