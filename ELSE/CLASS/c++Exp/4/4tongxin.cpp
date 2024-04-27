<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\4\4tongxin.cpp
 * @Description: 实现一个通讯录程序。实现功能：存取、显示、删除记录、查询记录等功能。
 */
=======

>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define a struct to represent a contact
struct Contact
{
    string name;
    string address;
    string postal_code;
    string phone_number;
    string email;
};

// Define a vector to store all contact information
vector<Contact> contacts;

// Add contact
<<<<<<< HEAD
/**
 * @description: 添加一个联系人，包括姓名、地址、邮编、电话、邮箱，将其存入到vector中
 * @return {*}
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void add_contact()
{
    Contact c;
    cout << "Please enter the contact name:";
    getline(cin, c.name);
    cout << "Please enter the contact address:";
    getline(cin, c.address);
    cout << "Please enter the postal code of the contact person:";
    getline(cin, c.postal_code);
    cout << "Please enter the contact phone number:";
    getline(cin, c.phone_number);
    cout << "Please enter the contact email:";
    getline(cin, c.email);
    contacts.push_back(c);
    cout << "Contact added" << endl;
}

// Delete contact
<<<<<<< HEAD
/**
 * @description: 删除一个联系人，根据姓名查找，找到后删除
 * @return {*}
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void delete_contact()
{
    string name;
    cout << "Please enter the name of the contact you want to delete:";
    getline(cin, name);
<<<<<<< HEAD
    for (int i = 0; i < contacts.size(); i++) // 遍历联系人向量
=======
    for (int i = 0; i < contacts.size(); i++)
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    {
        if (contacts[i].name == name)
        {
            contacts.erase(contacts.begin() + i);
            cout << "Contact deleted" << endl;
            return;
        }
    }
    cout << "The contact was not found" << endl;
}

// Search contact
<<<<<<< HEAD
/**
 * @description: 查找一个联系人，根据姓名查找，找到后输出联系人信息
 * @return {*}
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void search_contact()
{
    string name;
    cout << "Please enter the name of the contact you want to query:";
    getline(cin, name);
    for (int i = 0; i < contacts.size(); i++)
    {
        if (contacts[i].name == name)
        {
            cout << "Name:" << contacts[i].name << endl;
            cout << "Address:" << contacts[i].address << endl;
            cout << "Postal Code:" << contacts[i].postal_code << endl;
            cout << "Telephone Number:" << contacts[i].phone_number << endl;
            cout << "E-mail:" << contacts[i].email << endl;
            return;
        }
    }
    cout << "The contact was not found" << endl;
}

// Display all contacts
<<<<<<< HEAD
/**
 * @description: 输出所有联系人信息
 * @return {*}
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void show_contacts()
{
    if (contacts.size() == 0)
    {
        cout << "Don't have any contacts" << endl;
        return;
    }
    for (int i = 0; i < contacts.size(); i++)
    {
        cout << "Contact person " << i + 1 << ":" << endl;
        cout << "Name:" << contacts[i].name << endl;
        cout << "Address:" << contacts[i].address << endl;
        cout << "Postal Code:" << contacts[i].postal_code << endl;
        cout << "Telephone Number:" << contacts[i].phone_number << endl;
        cout << "E-mail:" << contacts[i].email << endl;
    }
}

int main()
{
    int choice;
<<<<<<< HEAD
    while (true) // 选择菜单页面
=======
    while (true)
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    {
        cout << "Please select an operation:" << endl;
        cout << "1. Add contact" << endl;
        cout << "2. Delete contact" << endl;
        cout << "3. Search contact" << endl;
        cout << "4. Show all contacts" << endl;
        cout << "0. Exit program" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            add_contact();
            break;
        case 2:
            delete_contact();
            break;
        case 3:
            search_contact();
            break;
        case 4:
            show_contacts();
            break;
        case 0:
            return 0;
        default:
            cout << "Invilad input" << endl;
            break;
        }
    }
    return 0;
}