/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\temp.cpp
 * @Description: 
 */
void myFunction(int* arr, int size) {
    // 对数组进行操作，可以使用arr[i]来访问数组元素
}
void myFunction(int arr[], int size) {
    // 对数组进行操作，可以使用arr[i]来访问数组元素
}

void matrix_multiply(int a[4][3], int b[3][2], int c[4][2])
{
    for (int i = 0; i < 4; i++) // i表示A矩阵的行
    {
        for (int j = 0; j < 2; j++) // j表示B矩阵的列
        {
            c[i][j] = 0; // 初始化
            for (int k = 0; k < 3; k++) // k表示A矩阵的列/B矩阵的行
            {
                c[i][j] += a[i][k] * b[k][j]; // 矩阵乘法
            }
        }
    }
}

void myFunction(int (*arr)[3], int size) {
    // 对数组进行操作，可以使用arr[i][j]来访问数组元素
}
void myFunction(int arr[][3], int size) {
    // 对数组进行操作，可以使用arr[i][j]来访问数组元素
}


#include <iostream>
using namespace std;

void averscore(int (*psco)[5], int avsco[])
{
    for (int i = 0; i < 5; i++)
    {
        int sum = 0;
        for (int j = 0; j < 5; j++)
        {
            sum += *(*(psco + i) + j);
        }
        avsco[i] = sum / 5;
    }
}

int avercourse(int (*psco)[5], int n)
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += *(*(psco + i) + n - 1);
    }
    return sum / 5;
}

int main()
{
    int num[5] = {1, 2, 3, 4, 5};
    int sco[5][5] = {0};
    int avsco[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << "Student " << num[i] << ", Course " << j + 1 << ": ";
            cin >> *(*(sco + i) + j);
        }
    }
    averscore(sco, avsco);
    for (int i = 0; i < 5; i++)
    {
        cout << "Student " << num[i] << "'s scores: ";
        for (int j = 0; j < 5; j++)
        {
            cout << *(*(sco + i) + j) << " ";
        }
        cout << "Average: " << avsco[i] << endl;
    }
    int t;
    cout << "Which course do you want to know the average score of? ";
    cin >> t;
    cout << "Average score of Course " << t << ": " << avercourse(sco, t) << endl;
    return 0;
}


int* createArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    return arr;
}

int (*sum)(int, int);

int add(int a, int b) {
    return a + b;
}

// 将add函数的地址赋值给sum函数指针
// sum = &add;

// 通过函数指针调用函数
int result = (*sum)(2, 3);

#include <iostream>
using namespace std;

struct Date
{
    int year;
    int month;
    int day;
};

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysOfMonth(int year, int month)
{
    switch (month)
    {
    case 2:
        return isLeapYear(year) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}

int main()
{
    Date* date = new Date; // 创建结构体变量的指针

    while (true)
    {
        cout << "Input year, month, day: ";
        cin >> date->year >> date->month >> date->day; // 使用指针方法访问结构体变量的成员
        if (date->year == 0 && date->month == 0 && date->day == 0)
        {
            break;
        }
        if (date->year < 0 || date->month < 1 || date->month > 12 || date->day < 1 || date->day > daysOfMonth(date->year, date->month))
        {
            cout << "Invalid date" << endl;
            continue;
        }
        int days = 0;
        for (int i = 1; i < date->month; i++)
        {
            days += daysOfMonth(date->year, i);
        }
        days += date->day;

        cout << date->year << "." << date->month << "." << date->day
             << " is the " << days << "th day of the year" << endl;
    }

    delete date; // 释放动态分配的内存
    return 0;
}

typedef struct node
{
    int elem;
    node *prev; // 新增指向前一个节点的指针
    node *next;
} Node;

typedef struct list
{
    Node *head;
    Node *tail;
} List;

if (mylist.head == NULL)
{
    mylist.head = mylist.tail = pNode;
    pNode->prev = NULL; // 新增代码，将头节点的prev指针置为NULL
}
else
{
    pNode->prev = mylist.tail;  // 将新节点的prev指针指向当前尾节点
    mylist.tail->next = pNode;  // 尾节点的next指针指向新节点
    mylist.tail = pNode;        // 将尾指针指向新节点
}

Node *pNode = mylist.head;
cout << "Link elements:";
while (pNode != NULL)
{
    cout << pNode->elem << " ";
    Node *pNext = pNode->next;
    delete pNode;
    pNode = pNext;
}


friend ostream &operator<<(ostream &os, const String &s)
{
    os << s.str;
    return os;
}

friend istream &operator>>(istream &is, String &s)
{
    const int bufferSize = 100;  // 缓冲区大小
    char buffer[bufferSize];    // 临时缓冲区

    is.getline(buffer, bufferSize);  // 从输入流中读取一行数据到缓冲区
    s = buffer;                      // 将缓冲区中的数据赋值给String对象

    return is;
}
