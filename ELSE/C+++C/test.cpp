// AddressBook.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "AddressBook.h"
#include <CommCtrl.h>
#include <iostream>
#include <string>
// 在头文件中包含Windows API
#include <Windows.h>

using namespace std;

// 通信录管理系统
class ContactManager
{
private:
    struct Contact
    {
        string name;
        string phoneNumber;
        string category;
        string email;
        Contact *next;
    };

    Contact *head;
    int itemCount;

public:
    ContactManager()
    {
        head = nullptr;
        itemCount = 0;
    }

    // 查看通信录
    void viewContacts()
    {
        if (head == nullptr)
        {
            cout << "通信录为空\n";
            return;
        }

        Contact *current = head;
        while (current != nullptr)
        {
            cout << "姓名: " << current->name << endl;
            cout << "电话号码: " << current->phoneNumber << endl;
            cout << "分类: " << current->category << endl;
            cout << "电子邮件: " << current->email << endl;
            cout << endl;

            current = current->next;
        }
    }

    // 增加联系人
    void addContact()
    {
        if (itemCount >= 15)
        {
            cout << "存储空间已满，不能再录入新数据\n";
            return;
        }

        cout << "请输入姓名：";
        string name;
        cin >> name;

        cout << "请输入电话号码：";
        string phoneNumber;
        cin >> phoneNumber;

        cout << "请选择分类（A-办公类，B-个人类，C-商务类）：";
        char categoryChoice;
        cin >> categoryChoice;

        string category;
        switch (categoryChoice)
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

        // 检查是否已存在相同姓名和电话号码的联系人
        Contact *current = head;
        while (current != nullptr)
        {
            if (current->name == name && current->phoneNumber == phoneNumber)
            {
                cout << "数据录入重复\n";
                return;
            }
            current = current->next;
        }

        // 创建新的联系人节点
        Contact *newContact = new Contact;
        newContact->name = name;
        newContact->phoneNumber = phoneNumber;
        newContact->category = category;
        newContact->email = email;
        newContact->next = nullptr;

        // 按递增顺序插入联系人
        if (head == nullptr || name < head->name)
        {
            newContact->next = head;
            head = newContact;
        }
        else
        {
            Contact *prev = nullptr;
            current = head;
            while (current != nullptr && name > current->name)
            {
                prev = current;
                current = current->next;
            }

            prev->next = newContact;
            newContact->next = current;
        }

        cout << "联系人已添加\n";
        itemCount++;
    }

    // 拔号
    void dialContact()
    {
        if (head == nullptr)
        {
            cout << "通信录为空\n";
            return;
        }

        cout << "通信录中的联系人：\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << endl;
            current = current->next;
        }

        cout << "请选择联系人姓名：";
        string name;
        cin >> name;

        current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                cout << "拨号中...\n";
                for (char c : current->phoneNumber)
                {
                    cout << c;
                    // 在代码中播放滴滴声音
                    MessageBeep(MB_ICONASTERISK);
                    Sleep(500); // 延迟显示每个数字的效果
                }
                cout << endl;
                return;
            }
            current = current->next;
        }

        cout << "未找到联系人\n";
    }

    // 修改联系人
    void modifyContact()
    {
        if (head == nullptr)
        {
            cout << "通信录为空\n";
            return;
        }

        cout << "通信录中的联系人：\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << endl;
            current = current->next;
        }

        cout << "请选择要修改的联系人姓名：";
        string name;
        cin >> name;

        current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                cout << "请输入新的电话号码：";
                string phoneNumber;
                cin >> phoneNumber;

                current->phoneNumber = phoneNumber;
                cout << "联系人已修改\n";
                return;
            }
            current = current->next;
        }

        cout << "未找到联系人\n";
    }

    // 删除联系人
    void deleteContact()
    {
        if (head == nullptr)
        {
            cout << "通信录为空\n";
            return;
        }

        cout << "通信录中的联系人：\n";
        Contact *current = head;
        while (current != nullptr)
        {
            cout << current->name << endl;
            current = current->next;
        }

        cout << "请选择要删除的联系人姓名：";
        string name;
        cin >> name;

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

// 全局变量:

// 此代码模块中包含的函数的前向声明:

// 通信录管理系统对象
ContactManager manager;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ADDRESSBOOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ADDRESSBOOK));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ADDRESSBOOK));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ADDRESSBOOK);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    // 创建一个按钮
    HWND hButton = CreateWindow(TEXT("button"), TEXT("添加联系人"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                10, 10, 100, 30, hWnd, (HMENU)IDM_ADD, hInstance, NULL);
    HWND hButton2 = CreateWindow(TEXT("button"), TEXT("查看联系人"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 10, 50, 100, 30, hWnd, (HMENU)IDM_VIEW, hInstance, NULL);
    HWND hButton3 = CreateWindow(TEXT("button"), TEXT("删除联系人"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 10, 90, 100, 30, hWnd, (HMENU)IDM_DELETE, hInstance, NULL);
    HWND hButton4 = CreateWindow(TEXT("button"), TEXT("退出"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 10, 130, 100, 30, hWnd, (HMENU)IDM_EXIT, hInstance, NULL);
    HWND hButton5 = CreateWindow(TEXT("button"), TEXT("保存"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 10, 170, 100, 30, hWnd, (HMENU)IDM_SAVE, hInstance, NULL);
    HWND hButton6 = CreateWindow(TEXT("button"), TEXT("读取"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 10, 210, 100, 30, hWnd, (HMENU)IDM_READ, hInstance, NULL);
    HWND hButton7 = CreateWindow(TEXT("button"), TEXT("修改"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 10, 250, 100, 30, hWnd, (HMENU)IDM_CHANGE, hInstance, NULL);
    HWND hButton8 = CreateWindow(TEXT("button"), TEXT("查找"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                 10, 290, 100, 30, hWnd, (HMENU)IDM_FIND, hInstance, NULL);
    HWND hListView = CreateWindowW(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 500, 500, hWnd, nullptr, hInstance, nullptr);
    // 设置列表视图控件样式
    ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT);

    // 添加列表视图控件的列
    LVCOLUMN lvColumn;
    lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
    lvColumn.cx = 100;

    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        lvColumn.pszText = const_cast<wchar_t *>(columnHeaders[i]);
        ListView_InsertColumn(hListView, i, &lvColumn);
    }

    if (!hWnd)
    {
        return FALSE;
    }
    // hCurrentPage = hWnd; // 设置当前页面为主窗口

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_VIEW:
            // 隐藏当前窗口，进入新窗口，生成返回按钮
            //  创建第二个页面窗口
            // hSecondPage = CreateWindowW(szWindowClass, L"添加学生", WS_OVERLAPPEDWINDOW,
            //     CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);

            //// 隐藏当前页面并显示第二个页面
            // ShowWindow(hCurrentPage, SW_HIDE);
            // ShowWindow(hSecondPage, SW_SHOW);

            manager.viewContacts();
            break;
        case IDM_ADD:
            manager.addContact();
            break;
        case IDM_DIAL:
            manager.dialContact();
            break;
        case IDM_MODIFY:
            manager.modifyContact();
            break;
        case IDM_DELETE:
            manager.deleteContact();
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
