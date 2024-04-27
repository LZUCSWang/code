#include <iostream>
#include <string>
using namespace std;

// ͨ��¼��Ŀ�ṹ��
struct Contact
{
    string name;
    string phoneNumber;
    string category;
    string email;
    Contact *next;
};

// ͨ��¼������
class ContactManager
{
private:
    Contact *head; // ����ͷָ��
    int itemCount; // ͨ��¼��Ŀ����

public:
    // ���캯��
    ContactManager()
    {
        head = nullptr;
        itemCount = 0;
    }

    // �����������ͷ��ڴ�
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

    // �鿴����
    void viewContacts()
    {
        cout << "��ѡ��Ҫ�鿴�����\n";
        cout << "A. �칫��\n";
        cout << "B. ������\n";
        cout << "C. ������\n";
        char choice;
        cin >> choice;

        string category;
        switch (choice)
        {
        case 'A':
            category = "�칫��";
            break;
        case 'B':
            category = "������";
            break;
        case 'C':
            category = "������";
            break;
        default:
            cout << "��Ч��ѡ��\n";
            return;
        }

        cout << "����\t�绰����\n";
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

    // ���ӹ���
    void addContact()
    {
        if (itemCount >= 15)
        {
            cout << "ͨ��¼�������޷����������\n";
            return;
        }

        cout << "������������";
        string name;
        cin >> name;

        cout << "������绰���룺";
        string phoneNumber;
        cin >> phoneNumber;

        // ����Ƿ����ظ��������͵绰����
        Contact *current = head;
        while (current != nullptr)
        {
            if (current->name == name && current->phoneNumber == phoneNumber)
            {
                cout << "����¼���ظ���ȡ��¼��\n";
                return;
            }
            current = current->next;
        }

        cout << "��ѡ����ࣺ\n";
        cout << "A. �칫��\n";
        cout << "B. ������\n";
        cout << "C. ������\n";
        char choice;
        cin >> choice;

        string category;
        switch (choice)
        {
        case 'A':
            category = "�칫��";
            break;
        case 'B':
            category = "������";
            break;
        case 'C':
            category = "������";
            break;
        default:
            cout << "��Ч��ѡ��\n";
            return;
        }

        cout << "����������ʼ���";
        string email;
        cin >> email;

        // �����µ�ͨ��¼��Ŀ
        Contact *newContact = new Contact;
        newContact->name = name;
        newContact->phoneNumber = phoneNumber;
        newContact->category = category;
        newContact->email = email;
        newContact->next = nullptr;

        // ���뵽�����У����������ֵ���
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

        cout << "�����������\n";
        itemCount++;
    }

    // �κŹ���
    void dialContact()
    {
        cout << "ͨ��¼�е���Ա��\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << "\n";
            current = current->next;
        }

        cout << "��ѡ��Ҫ�������ϵ�ˣ�\n";
        string name;
        cin >> name;

        current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                cout << "������...\n";
                for (char digit : current->phoneNumber)
                {
                    cout << digit << " ";
                    // ģ��κ����������Ը�����Ҫ�����޸�
                    cout << "Dial tone...\n";
                }
                cout << "\n";
                return;
            }
            current = current->next;
        }

        cout << "δ�ҵ���ϵ��\n";
    }

    // �޸Ĺ���
    void modifyContact()
    {
        cout << "ͨ��¼�е���Ա��\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << "\n";
            current = current->next;
        }

        cout << "��ѡ��Ҫ�޸ĵ���ϵ�ˣ�\n";
        string name;
        cin >> name;

        current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                cout << "��ѡ��Ҫ�޸ĵ����ݣ�\n";
                cout << "1. ����\n";
                cout << "2. �绰����\n";
                cout << "3. ����\n";
                cout << "4. �����ʼ�\n";
                int choice;
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    cout << "�������µ�������";
                    string newName;
                    cin >> newName;
                    current->name = newName;
                    cout << "�������޸�\n";
                    break;
                }
                case 2:
                {
                    cout << "�������µĵ绰���룺";
                    string newPhoneNumber;
                    cin >> newPhoneNumber;
                    current->phoneNumber = newPhoneNumber;
                    cout << "�绰�������޸�\n";
                    break;
                }
                case 3:
                {
                    cout << "��ѡ���µķ��ࣺ\n";
                    cout << "A. �칫��\n";
                    cout << "B. ������\n";
                    cout << "C. ������\n";
                    char categoryChoice;
                    cin >> categoryChoice;

                    string newCategory;
                    switch (categoryChoice)
                    {
                    case 'A':
                        newCategory = "�칫��";
                        break;
                    case 'B':
                        newCategory = "������";
                        break;
                    case 'C':
                        newCategory = "������";
                        break;
                    default:
                        cout << "��Ч��ѡ��\n";
                        return;
                    }

                    current->category = newCategory;
                    cout << "�������޸�\n";
                    break;
                }
                case 4:
                {
                    cout << "�������µĵ����ʼ���";
                    string newEmail;
                    cin >> newEmail;
                    current->email = newEmail;
                    cout << "�����ʼ����޸�\n";
                    break;
                }
                default:
                    cout << "��Ч��ѡ��\n";
                    return;
                }

                return;
            }
            current = current->next;
        }

        cout << "δ�ҵ���ϵ��\n";
    }

    // ɾ������
    void deleteContact()
    {
        cout << "ͨ��¼�е���Ա��\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << "\n";
            current = current->next;
        }

        cout << "��ѡ��Ҫɾ������ϵ�ˣ�\n";
        string name;
        cin >> name;

        if (head == nullptr)
        {
            cout << "ͨ��¼Ϊ��\n";
            return;
        }

        if (head->name == name)
        {
            Contact *temp = head;
            head = head->next;
            delete temp;
            cout << "��ϵ����ɾ��\n";
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
                cout << "��ϵ����ɾ��\n";
                itemCount--;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "δ�ҵ���ϵ��\n";
    }
};

int main()
{
    ContactManager manager;

    while (true)
    {
        cout << "\n��ѡ�������\n";
        cout << "1. �鿴ͨ��¼\n";
        cout << "2. ������ϵ��\n";
        cout << "3. �κ�\n";
        cout << "4. �޸���ϵ��\n";
        cout << "5. ɾ����ϵ��\n";
        cout << "6. �˳�\n";

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
            cout << "��Ч��ѡ��\n";
            break;
        }
    }

    return 0;
}
