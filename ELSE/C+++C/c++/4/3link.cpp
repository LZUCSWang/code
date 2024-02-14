<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\4\3link.cpp
 * @Description: 设计一个单向链表,要求实现链表的建立、遍历和释放节点空间的功能。
 */

=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
#include <iostream>
using namespace std;

// 定义链表节点类型
typedef struct node
{
    int elem;
    node *next;
} Node;

// 定义链表类型
typedef struct list
{
    Node *head; // 链表头指针
    Node *tail; // 链表尾指针
} List;

int main()
{
    List mylist = {NULL, NULL}; // 初始化链表为空
    int input = -1;
    cout << "Please input integers to build the link(0 TO END):" << endl;
    while (input != 0)
    {
        cin >> input;
        if (input != 0)
        {
            Node *pNode = new Node; // 动态分配节点空间
            if (pNode == NULL)      // 判断分配是否成功
            {
                cout << "Memory insufficient!" << endl;
                break;
            }
            pNode->elem = input;     // 节点存放值
            pNode->next = NULL;      // 节点指针赋值为空
            if (mylist.head == NULL) // 如果是第一个节点，链表为空
            {
                mylist.head = mylist.tail = pNode; // 第一个节点既是头也是尾。
            }
            else
            {
                mylist.tail->next = pNode; // 尾节点的指针指向新节点，即将新节点加到链表中
                mylist.tail = pNode;       // 新节点加入到链表尾后，让尾指针指向该节点。
            }
        }
    }
    // 顺序遍历链表并释放节点空间
    Node *pNode = mylist.head; // 让一个指针pNode 指向链表头
    cout << "Link elements:";
    while (pNode != NULL)
    {
<<<<<<< HEAD
        cout << pNode->elem << " "; // 输出节点存储的数据
        Node *pNext = pNode->next;  // 保存下一个节点的指针
        delete pNode;               // 释放当前节点的空间
        pNode = pNext;              // 让pNode 指向下一个节点。
=======
        cout << pNode->elem<<" ";       // 输出节点存储的数据
        Node *pNext = pNode->next; // 保存下一个节点的指针
        delete pNode;              // 释放当前节点的空间
        pNode = pNext;             // 让pNode 指向下一个节点。
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    }
    return 0;
}
