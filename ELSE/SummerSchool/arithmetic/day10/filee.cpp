#include <bits/stdc++.h>
using namespace std;
struct node
{
    int hights;
    map<string, node *> files;
    map<string, node *> next_pos;
    node()
    {
        hights = 0;
    };
} * root;
void dfs(node *cNode)
{
    if (cNode == NULL)
        return;
    map<string, node *>::iterator it1, it2;
    for (it1 = cNode->next_pos.begin(); it1 != cNode->next_pos.end(); it1++)
    {
        for (int ii = 0; ii < cNode->hights + 1; ii++)
        {
            cout << "  ";
        }
        cout << it1->first << endl;
        dfs(it1->second);
    }
    for (it2 = cNode->files.begin(); it2 != cNode->files.end(); it2++)
    {
        for (int ii = 0; ii < cNode->hights + 1; ii++)
        {
            cout << "  ";
        }
        cout << it2->first << endl;
    }
    delete cNode;
}
int main()
{
    int n;
    cin >> n;
    root = new node();
    while (n--)
    {
        string s, t;
        cin >> s;
        node *cNode = root;
        for (int i = 0; s[i]; i++)
        {
            if (s[i] != '\\')
            {
                t += s[i];
            }
            else
            {
                if (cNode->next_pos[t] == NULL)
                {
                    node *tNode = new node();
                    tNode->hights = cNode->hights + 1;
                    cNode->next_pos[t] = tNode;
                    cNode = tNode;
                }
                else
                {
                    cNode = cNode->next_pos[t];
                }
                t = "";
            }
        }
        if (t != "")
        {
            if (cNode->files[t] != NULL)
            {
                cNode = cNode->files[t];
            }
            else
            {
                node *tNode = new node();
                tNode->hights = cNode->hights + 1;
                cNode->files[t] = tNode;
                cNode = tNode;
            }
        }
    }
    printf("root\n");
    dfs(root);
    return 0;
}
