#include <iostream>
#include <string>
using namespace std;

// 通信录条目结构体
struct Contact
{
    string name;
    string phoneNumber;
    string category;
    string email;
    Contact *next;
};

// 通信录管理类
class ContactManager
{
private:
    Contact *head; // 链表头指针
    int itemCount; // 通信录条目数量

public:
    // 构造函数
    ContactManager()
    {
        head = nullptr;
        itemCount = 0;
    }

    // 析构函数，释放内存
    ~ContactManager()
    {
        Contact *current = head;
        while (current != nullptr)
        {
            Contact *next = current->next;
            delete current;
            current = next;
        }
    }

    // 查看功能
    void viewContacts()
    {
        cout << "请选择要查看的类别：\n";
        cout << "A. 办公类\n";
        cout << "B. 个人类\n";
        cout << "C. 商务类\n";
        char choice;
        cin >> choice;

        string category;
        switch (choice)
        {
        case 'A':
            category = "办公类";
            break;
        case 'B':
            category = "个人类";
            break;
        case 'C':
            category = "商务类";
            break;
        default:
            cout << "无效的选择\n";
            return;
        }

        cout << "姓名\t电话号码\n";
        Contact *current = head;
        while (current != nullptr)
        {
            if (current->category == category)
            {
                cout << current->name << "\t" << current->phoneNumber << "\n";
            }
            current = current->next;
        }
    }

    // 增加功能
    void addContact()
    {
        if (itemCount >= 15)
        {
            cout << "通信录已满，无法添加新数据\n";
            return;
        }

        cout << "请输入姓名：";
        string name;
        cin >> name;

        cout << "请输入电话号码：";
        string phoneNumber;
        cin >> phoneNumber;

        // 检查是否有重复的姓名和电话号码
        Contact *current = head;
        while (current != nullptr)
        {
            if (current->name == name && current->phoneNumber == phoneNumber)
            {
                cout << "数据录入重复，取消录入\n";
                return;
            }
            current = current->next;
        }

        cout << "请选择分类：\n";
        cout << "A. 办公类\n";
        cout << "B. 个人类\n";
        cout << "C. 商务类\n";
        char choice;
        cin >> choice;

        string category;
        switch (choice)
        {
        case 'A':
            category = "办公类";
            break;
        case 'B':
            category = "个人类";
            break;
        case 'C':
            category = "商务类";
            break;
        default:
            cout << "无效的选择\n";
            return;
        }

        cout << "请输入电子邮件：";
        string email;
        cin >> email;

        // 创建新的通信录条目
        Contact *newContact = new Contact;
        newContact->name = name;
        newContact->phoneNumber = phoneNumber;
        newContact->category = category;
        newContact->email = email;
        newContact->next = nullptr;

        // 插入到链表中（按姓名的字典序）
        if (head == nullptr || name < head->name)
        {
            newContact->next = head;
            head = newContact;
        }
        else
        {
            Contact *current = head;
            while (current->next != nullptr && current->next->name < name)
            {
                current = current->next;
            }
            newContact->next = current->next;
            current->next = newContact;
        }

        cout << "新数据已添加\n";
        itemCount++;
    }

    // 拔号功能
    void dialContact()
    {
        cout << "通信录中的人员：\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << "\n";
            current = current->next;
        }

        cout << "请选择要拨打的联系人：\n";
        string name;
        cin >> name;

        current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                cout << "拨号中...\n";
                for (char digit : current->phoneNumber)
                {
                    cout << digit << " ";
                    // 模拟拔号声音，可以根据需要自行修改
                    cout << "Dial tone...\n";
                }
                cout << "\n";
                return;
            }
            current = current->next;
        }

        cout << "未找到联系人\n";
    }

    // 修改功能
    void modifyContact()
    {
        cout << "通信录中的人员：\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << "\n";
            current = current->next;
        }

        cout << "请选择要修改的联系人：\n";
        string name;
        cin >> name;

        current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                cout << "请选择要修改的数据：\n";
                cout << "1. 姓名\n";
                cout << "2. 电话号码\n";
                cout << "3. 分类\n";
                cout << "4. 电子邮件\n";
                int choice;
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    cout << "请输入新的姓名：";
                    string newName;
                    cin >> newName;
                    current->name = newName;
                    cout << "姓名已修改\n";
                    break;
                }
                case 2:
                {
                    cout << "请输入新的电话号码：";
                    string newPhoneNumber;
                    cin >> newPhoneNumber;
                    current->phoneNumber = newPhoneNumber;
                    cout << "电话号码已修改\n";
                    break;
                }
                case 3:
                {
                    cout << "请选择新的分类：\n";
                    cout << "A. 办公类\n";
                    cout << "B. 个人类\n";
                    cout << "C. 商务类\n";
                    char categoryChoice;
                    cin >> categoryChoice;

                    string newCategory;
                    switch (categoryChoice)
                    {
                    case 'A':
                        newCategory = "办公类";
                        break;
                    case 'B':
                        newCategory = "个人类";
                        break;
                    case 'C':
                        newCategory = "商务类";
                        break;
                    default:
                        cout << "无效的选择\n";
                        return;
                    }

                    current->category = newCategory;
                    cout << "分类已修改\n";
                    break;
                }
                case 4:
                {
                    cout << "请输入新的电子邮件：";
                    string newEmail;
                    cin >> newEmail;
                    current->email = newEmail;
                    cout << "电子邮件已修改\n";
                    break;
                }
                default:
                    cout << "无效的选择\n";
                    return;
                }

                return;
            }
            current = current->next;
        }

        cout << "未找到联系人\n";
    }

    // 删除功能
    void deleteContact()
    {
        cout << "通信录中的人员：\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << "\n";
            current = current->next;
        }

        cout << "请选择要删除的联系人：\n";
        string name;
        cin >> name;

        if (head == nullptr)
        {
            cout << "通信录为空\n";
            return;
        }

        if (head->name == name)
        {
            Contact *temp = head;
            head = head->next;
            delete temp;
            cout << "联系人已删除\n";
            itemCount--;
            return;
        }

        Contact *prev = head;
        current = head->next;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                prev->next = current->next;
                delete current;
                cout << "联系人已删除\n";
                itemCount--;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "未找到联系人\n";
    }
};

int main()
{
    ContactManager manager;

    while (true)
    {
        cout << "\n请选择操作：\n";
        cout << "1. 查看通信录\n";
        cout << "2. 增加联系人\n";
        cout << "3. 拔号\n";
        cout << "4. 修改联系人\n";
        cout << "5. 删除联系人\n";
        cout << "6. 退出\n";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            manager.viewContacts();
            break;
        case 2:
            manager.addContact();
            break;
        case 3:
            manager.dialContact();
            break;
        case 4:
            manager.modifyContact();
            break;
        case 5:
            manager.deleteContact();
            break;
        case 6:
            return 0;
        default:
            cout << "无效的选择\n";
            break;
        }
    }

    return 0;
}
