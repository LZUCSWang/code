#include <iostream>
#include <string>

using namespace std;

class Date
{
private:
    int year;
    int month;
    int day;

public:
    void SetYear(int year)
    {
        this->year = year;
    }
    void SetMonth(int month)
    {
        this->month = month;
    }
    void SetDay(int day)
    {
        this->day = day;
    }
    int GetYear()
    {
        return year;
    }
    int GetMonth()
    {
        return month;
    }
    int GetDay()
    {
        return day;
    }
};

class Employee
{
private:
    int number;
    string name;
    string sex;
    Date birth;
    string position;

public:
    Employee() {}
    Employee(int num, string n, string s, int y, int m, int d, string pos)
    {
        number = num;
        name = n;
        sex = s;
        birth.SetYear(y);
        birth.SetMonth(m);
        birth.SetDay(d);
        position = pos;
    }
    Employee(int num, string n, string pos)
    {
        number = num;
        name = n;
        position = pos;
    }
    void ModifyInfo(string n, string pos)
    {
        name = n;
        position = pos;
    }
    void DisplayInfo()
    {
        cout << "====================" << endl;
        cout << "Employee Number: " << number << endl;
        cout << "Employee Name: " << name << endl;
        cout << "Employee Gender: " << sex << endl;
        cout << "Employee Date of Birth: " << birth.GetYear() << " / " << birth.GetMonth() << " / " << birth.GetDay() << endl;
        cout << "Employee Position: " << position << endl;
    }
    friend void SearchByNumber(Employee *empList, int n, int num);
    friend void SearchByName(Employee *empList, int n, string name);
    int getNumber()
    {
        return number;
    }
};

struct Node
{
    Employee emp;
    Node *next;
};

Node *AddNode(Node *head, Employee emp)
{
    Node *newNode = new Node;
    newNode->emp = emp;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return head;
}

void SearchByNumber(Node *head, int num)
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->emp.getNumber() == num)
        {
            temp->emp.DisplayInfo();
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with number " << num << " not found!" << endl;
}

void SearchByName(Node *head, string name)
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->emp.name == name)
        {
            temp->emp.DisplayInfo();
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with name " << name << " not found!" << endl;
}

int main()
{
    Node *head = NULL; // 头节点
    int choice = 0;
    int num;
    string name, s;
    int y, m, d;
    string pos;
    while (choice != 6)
    {
        cout << "选择操作：\n1. 输入员工信息\n2. 显示员工信息\n3. 修改员工信息\n4. 按员工编号查找\n5. 按员工姓名查找\n6. 退出\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            int n;
            cout << "输入要添加的员工数量：";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "输入第 " << i + 1 << " 个员工的信息：" << endl;
                cout << "输入员工编号：";
                cin >> num;
                cout << "输入员工姓名：";
                cin >> name;
                cout << "输入员工性别：";
                cin >> s;
                cout << "输入员工出生年份：";
                cin >> y;
                cout << "输入员工出生月份：";
                cin >> m;
                cout << "输入员工出生日期：";
                cin >> d;
                cout << "输入员工职位：";
                cin >> pos;
                Employee emp(num, name, s, y, m, d, pos);
                head = AddNode(head, emp);
            }
            break;
        case 2:
            {
                Node *temp = head;
                while (temp != NULL)
                {
                    temp->emp.DisplayInfo();
                    temp = temp->next;
                }
            }
            break;
        case 3:
            cout << "输入要修改的员工编号：";
            cin >> num;
            cout << "输入新的员工姓名：";
            cin >> name;
            cout << "输入新的员工职位：";
            cin >> pos;
            {
                Node *temp = head;
                while (temp != NULL)
                {
                    if (temp->emp.getNumber() == num)
                    {
                        temp->emp.ModifyInfo(name, pos);
                        break;
                    }
                    temp = temp->next;
                }
            }
            break;
        case 4:
            cout << "输入要查找的员工编号：";
            cin >> num;
            SearchByNumber(head, num);
            break;
        case 5:
            cout << "输入要查找的员工姓名：";
            cin >> name;
            SearchByName(head, name);
            break;
        case 6:
            cout << "程序结束！" << endl;
            break;
        default:
            cout << "无效输入！" << endl;
            break;
        }
    }
    
    // 释放链表内存
    Node *temp = head;
    while (temp != NULL)
    {
        Node *current = temp;
        temp = temp->next;
        delete current;
    }

    return 0;
}
