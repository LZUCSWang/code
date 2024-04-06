#include <bits/stdc++.h>
using namespace std;
struct Node
{
    string val;
    string type;
    Node *l, *r;
    Node(string a, string b)
    {
        val = a;
        type = b;
        l = NULL;
        r = NULL;    
    }
};

stack<Node> op;//符号栈
vector<Node> pfix;//后缀表达式
map<string, int> prio;//运算符优先级

void ini()
{
    prio["$"] = 101;
    prio["-"] = 4; prio["+"] = 4;
    prio["*"] = 3; prio["/"] = 3;
    prio["("] = 99;
    prio[">"] = prio[">="] = prio["<"] = prio["<="] = prio["=="] = 6;
    prio["!="] = 7;
    prio["||"] = 11; prio["&&"] = 12;
    prio["!"] = 2;
    prio["$$"] = 100; 
    op.push(Node("$", "op"));
}

void print(Node *root, int wid)
{
    if (root == NULL)
        return ;
    cout << setw(3) << root->val;
    if (root->r == NULL)
        return ;
    cout << "..." << endl;
    if (root->val == "!")
        cout << setw(wid + 3) << "|" << endl;
    else
        cout << setw(wid) << "|" << setw(3) << "|" << endl;
    if (root->l != NULL)
        cout << setw(wid) << root->l->val;
    else
        cout << setw(wid) << " ";
    print(root->r, wid + 3);

}

void add(string val, string type)
{
    Node t(val, type);
    if (type == "op" || type == "delimiter")
    {
        if (val == ")")
        {
            while (op.top().val != "(")
            {
                Node temp3 = op.top(); op.pop();
                pfix.push_back(temp3);
            }
            op.pop();//去掉"("
        }
        else if (val == "(" || prio[val] < prio[op.top().val])
            op.push(t);
        else
        {
            while (prio[val] >= prio[op.top().val])
            {
                Node temp3 = op.top(); op.pop();
                pfix.push_back(temp3);
            }
            op.push(t); 
        }
    }
    else
    {
        pfix.push_back(t);
    }
}
int main()
{
    ini();//初始化相关

    ifstream fin("output6.txt", ios::in);
    if (!fin.is_open())
    {
        cout << "文件打不开" << endl;
        exit(0);
    }
    string buf;
    while (getline(fin, buf))//一边读入一边转化为后缀表达式
    {
        string val, type;
        //将buf分割
        int ind = buf.size();
        while (ind >= 0)
        {
            if (buf[ind] == ',')
                break;
            --ind;
        }
        for (int i = 1; i < ind; ++i)
            val += buf[i];
        for (int i = ind + 2; i < buf.size() - 1; ++i)
            type += buf[i];
        //cout << val << " " << type << endl;
        add(val, type);
    }
    add("$$", "op");
    //后缀表达式建立完毕
    Node *root = NULL;
    int i = 0;
    while (i < pfix.size())
    {
        if (pfix[i].type == "op")
        {
            if (root == NULL)
            {
                Node *t1 = new Node(pfix[i]);
                int temp1 = 2, temp2 = 3;
                if (t1->val == "!")
                {
                    Node *t2 = new Node(pfix[i - 1]);
                    t1->r = t2;
                    temp1--; temp2--;
                }
                else
                {
                    Node *t2 = new Node(pfix[i - 1]);
                    Node *t3 = new Node(pfix[i - 2]);
                    t1->l = t2;
                    t1->r = t3; 
                }
                root = t1;
                i -= temp1;
                for (int j = 0; j < temp2; ++j)
                    pfix.erase(pfix.begin() + i); 
            }
            else
            {
                Node *t1 = new Node(pfix[i]);
                int temp1 = 1, temp2 = 2;
                if (t1->val == "!")
                {
                    t1->r = root;
                    temp1--; temp2--;
                }
                else
                {
                    Node *t2 = new Node(pfix[i - 1]);
                    t1->r = root;
                    t1->l = t2;
                }
                root = t1;
                i -= temp1;
                for (int j = 0; j < temp2; ++j)
                    pfix.erase(pfix.begin() + i); 
            }
        }
        else
            ++i;
    }
    print(root, 3);
    return 0;
}