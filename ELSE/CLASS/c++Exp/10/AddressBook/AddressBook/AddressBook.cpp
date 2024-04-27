// AddressBook.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "AddressBook.h"

using namespace std;

string wstring2string(wstring wstr)
{
    string result;
    // 获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    // 宽字节编码转换成多字节编码
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    // 删除缓冲区并返回值
    result.append(buffer);
    delete[] buffer;
    return result;
}
wstring string2wstring(string str)
{
    wstring result;
    // 获取缓冲区大小，并申请空间，缓冲区大小按字符计算
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    TCHAR* buffer = new TCHAR[len + 1];
    // 多字节编码转换成宽字节编码
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0'; // 添加字符串结尾
    // 删除缓冲区并返回值
    result.append(buffer);
    delete[] buffer;
    return result;
}
// 通信录管理系统

//void write_student_file(string filename)
//{
//    ofstream outfile(filename);
//    if (!outfile.is_open())
//    {
//        cerr << "Error: can't open file " << filename << endl;
//        return;
//    }
//
//    for (const auto& s : students)
//    {
//        outfile << s.name << " , " << s.id << " , " << s.chinese << " , " << s.math << " , " << s.english << endl;
//    }
//
//    outfile.close();
//}

class ContactManager
{

public:
    Contact* head;
    int itemCount;
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

        Contact* current = head;
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
    void addContact(string name, string phoneNumber, string category, string email)
    {
        if (itemCount >= 15)
        {
            cout << "存储空间已满，不能再录入新数据\n";
            return;
        }

        /*cout << "请输入姓名：";
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
        cin >> email;*/

        // 检查是否已存在相同姓名和电话号码的联系人
        Contact* current = head;
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
        Contact* newContact = new Contact;
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
            Contact* prev = nullptr;
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
    string dialContact(string name)
    {
        if (head == nullptr)
        {
            cout << "通信录为空\n";
            return "";
        }

        cout << "通信录中的联系人：\n";
        Contact* current = head;
        while (current != nullptr)
        {
            cout << current->name << endl;
            current = current->next;
        }

        cout << "请选择联系人姓名：";
        //string name;
        //cin >> name;

        current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                //cout << "拨号中...\n";
                //for (char c : current->phoneNumber)
                //{
                //    cout << c;
                //    // 在代码中播放滴滴声音
                //    MessageBeep(MB_ICONASTERISK);
                //    Sleep(500); // 延迟显示每个数字的效果
                //}
                //cout << endl;
          
                return current->phoneNumber;
            }
            current = current->next;
        }

        cout << "未找到联系人\n";
        return "";
    }

    // 修改联系人
    void modifyContact(string name,string phoneNumber)
    {
        if (head == nullptr)
        {
            cout << "通信录为空\n";
            return;
        }

        cout << "通信录中的联系人：\n";
        Contact* current = head;
        while (current != nullptr)
        {
            cout << current->name << endl;
            current = current->next;
        }

        cout << "请选择要修改的联系人姓名：";
        current = head;
        while (current != nullptr)
        {
            if (current->name == name)
            {
                cout << "请输入新的电话号码：";

                current->phoneNumber = phoneNumber;
                cout << "联系人已修改\n";
                return;
            }
            current = current->next;
        }

        cout << "未找到联系人\n";
    }

    // 删除联系人
    void deleteContact(string name)
    {
        if (head == nullptr)
        {
            cout << "通信录为空\n";
            return;
        }

        cout << "通信录中的联系人：\n";
        Contact* current = head;
        while (current != nullptr)
        {
            cout << current->name << endl;
            current = current->next;
        }

        cout << "请选择要删除的联系人姓名：";
        //string name;
        //cin >> name;

        if (head->name == name)
        {
            Contact* temp = head;
            head = head->next;
            delete temp;
            cout << "联系人已删除\n";
            itemCount--;
            return;
        }

        Contact* prev = head;
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
void read_contact_file()
{
    OPENFILENAMEA ofn;
    CHAR szFile[MAX_PATH];

    ZeroMemory(&ofn, sizeof(ofn));
    ZeroMemory(szFile, sizeof(szFile));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "txt";

    if (GetOpenFileNameA(&ofn))
    {
        std::ifstream infile(ofn.lpstrFile);
        if (!infile.is_open())
        {
            std::cerr << "Error: can't open file " << ofn.lpstrFile << std::endl;
            return;
        }

        std::string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            std::string name, phoneNumber;
            string category;
            std::string email;

            std::string dummy;
            if (!(iss >> name >> dummy >> phoneNumber >> dummy >> category >> dummy >> email))
            {
                std::cerr << "Error: invalid student file format" << std::endl;
                return;
            }
            manager.addContact(name, phoneNumber, category, email);
        }
        infile.close();
    }
    return;
}

void SaveContactsToFile(HWND hWnd, Contact* head)
{
    OPENFILENAME ofn = { 0 };
    wchar_t filePath[MAX_PATH] = { 0 };

    // 初始化 OPENFILENAME 结构体
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrDefExt = L"txt";
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrTitle = L"Save As";
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

    // 打开文件选择框
    if (GetSaveFileName(&ofn))
    {
        std::ofstream file(ofn.lpstrFile);

        if (file.is_open())
        {
            Contact* current = head;

            while (current != nullptr)
            {
                file << current->name << " , " << current->phoneNumber << " , " << current->category <<" , " << current->email << endl;

                current = current->next;
            }
            file.close();
        }
        else
        {
            // 文件无法打开，处理错误
        }
    }
}

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
        600, 10, 100, 30, hWnd, (HMENU)IDM_ADD, hInstance, NULL);
    HWND hButton2 = CreateWindow(TEXT("button"), TEXT("导入联系人"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        600, 50, 100, 30, hWnd, (HMENU)IDM_VIEW, hInstance, NULL);
    HWND hButton3 = CreateWindow(TEXT("button"), TEXT("删除联系人"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        600, 90, 100, 30, hWnd, (HMENU)IDM_DELETE, hInstance, NULL);
    HWND hButton4 = CreateWindow(TEXT("button"), TEXT("修改联系人"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        600, 130, 100, 30, hWnd, (HMENU)IDM_MODIFY, hInstance, NULL);
    HWND hButton5 = CreateWindow(TEXT("button"), TEXT("保存并退出"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        600, 170, 100, 30, hWnd, (HMENU)IDM_EXIT, hInstance, NULL);
    HWND hButton6 = CreateWindow(TEXT("button"), TEXT("拨号联系人"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        600, 210, 100, 30, hWnd, (HMENU)IDM_DIAL, hInstance, NULL);
    hListView = CreateWindowW(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 550, 500, hWnd, nullptr, hInstance, nullptr);
    // 设置列表视图控件样式
    ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT);

    // 添加列表视图控件的列
    LVCOLUMN lvColumn;
    lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
    lvColumn.cx = 150;

    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        lvColumn.pszText = const_cast<wchar_t*>(columnHeaders[i]);
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
void fresh_list() {
    // 清空列表视图控件
    ListView_DeleteAllItems(hListView);
    Contact* item = manager.head;
    for (int i = 0; i < manager.itemCount; i++)
    {
        LVITEM lvItem;
        lvItem.mask = LVIF_TEXT;
        lvItem.iItem = i;
        lvItem.iSubItem = 0;
        wstring name = string2wstring(item->name);
        lvItem.pszText = &name[0]; // 插入姓名

        // 插入第一列的数据
        ListView_InsertItem(hListView, &lvItem);

        lvItem.iSubItem = 1;
        std::wstring phoneNumber = string2wstring(item->phoneNumber);
        lvItem.pszText = &phoneNumber[0]; // 插入电话
        ListView_SetItemText(hListView, i, 1, lvItem.pszText);

        lvItem.iSubItem = 2;
        std::wstring category = string2wstring(item->category);
        lvItem.pszText = &category[0]; // 插入学号
        ListView_SetItemText(hListView, i, 2, lvItem.pszText);

        lvItem.iSubItem = 3;
        std::wstring email = string2wstring(item->email);
        lvItem.pszText = &email[0]; // 插入学号
        ListView_SetItemText(hListView, i, 3, lvItem.pszText);

        item = item->next;
    }
}
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
        {
            // manager.viewContacts();
            read_contact_file();
            // 将manager中的联系人信息显示到列表视图控件中
            fresh_list();
        }
        break;
        case IDM_ADD:
        {
            hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                800, 110, 150, 20, hWnd, NULL, hInst, NULL);
            hTextBox2 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                800, 130, 150, 20, hWnd, NULL, hInst, NULL);
            hTextBox3 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                800, 150, 150, 20, hWnd, NULL, hInst, NULL);

            hlabel1 = CreateWindowW(L"STATIC", L"姓名", WS_CHILD | WS_VISIBLE,
                				750, 110, 50, 20, hWnd, NULL, hInst, NULL);
            hlabel2 = CreateWindowW(L"STATIC", L"电话", WS_CHILD | WS_VISIBLE,
                750, 130, 50, 20, hWnd, NULL, hInst, NULL);
            hlabel3 = CreateWindowW(L"STATIC", L"邮箱", WS_CHILD | WS_VISIBLE,
                750, 150, 50, 20, hWnd, NULL, hInst, NULL);

            hOfficialRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"办公类",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                800, 200, 100, 30,
                hWnd,
                NULL, // 修改为不同的标识符
                hInst,
                NULL);

            hIndividualRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"个人类",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                800, 230, 100, 30,
                hWnd,
                NULL, // 修改为不同的标识符
                hInst,
                NULL);
            hBusinessRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"商务类",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                800, 260, 100, 30,
                hWnd,
                NULL, // 修改为不同的标识符
                hInst,
                NULL);
            // 创建确认按钮
            hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
            mode = IDM_ADD;
        }
        break;
        case IDM_DIAL:
        {

            hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                800, 110, 100, 20, hWnd, NULL, hInst, NULL);
            hlabel1 = CreateWindowW(L"STATIC", L"姓名", WS_CHILD | WS_VISIBLE,
                				750, 110, 50, 20, hWnd, NULL, hInst, NULL);
            hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
            mode = IDM_DIAL;
        }
            break;
        case IDM_MODIFY:
        {
            hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                900, 110, 100, 20, hWnd, NULL, hInst, NULL);
            hTextBox2 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                				900, 130, 100, 20, hWnd, NULL, hInst, NULL);

            hlabel1= CreateWindowW(L"STATIC", L"姓名", WS_CHILD | WS_VISIBLE,
                750, 110, 100, 20, hWnd, NULL, hInst, NULL);
            hlabel2 = CreateWindowW(L"STATIC", L"电话(修改后）", WS_CHILD | WS_VISIBLE,
                750, 130, 100, 20, hWnd, NULL, hInst, NULL);
            hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
            //manager.modifyContact();
            mode = IDM_MODIFY;
        }
            break;
        case IDM_DELETE:
        {
            // manager.deleteContact();
            hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                800, 110, 100, 20, hWnd, NULL, hInst, NULL);
            hlabel1 = CreateWindowW(L"STATIC", L"姓名", WS_CHILD | WS_VISIBLE,
                				750, 110, 50, 20, hWnd, NULL, hInst, NULL);
            hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
            mode = IDM_DELETE;
        }
        break;
        case IDM_EXIT:
        {
            SaveContactsToFile(hWnd, manager.head);

            DestroyWindow(hWnd);
        }
            break;
        case IDM_CONFIRM:
        {
            switch (mode)
            {
            case IDM_ADD:
            {
                string name, phoneNumber, category, email;
                int officialCheckState = SendMessage(hOfficialRadioButton, BM_GETCHECK, 0, 0);
                int individualCheckState = SendMessage(hIndividualRadioButton, BM_GETCHECK, 0, 0);
                int businessCheckState = SendMessage(hBusinessRadioButton, BM_GETCHECK, 0, 0);
                if (officialCheckState == BST_CHECKED)
                {
                    category = "Official";
                }
                else if (individualCheckState == BST_CHECKED)
                {
                    category = "Individual";
                }
                else if (businessCheckState == BST_CHECKED)
                {
                    category = "Business";
                }
                // 获取第一个输入框的文本
                int textLength = GetWindowTextLengthW(hTextBox1);
                wchar_t* buffer = new wchar_t[textLength + 1];
                GetWindowTextW(hTextBox1, buffer, textLength + 1);
                name = wstring2string(buffer);
                delete[] buffer;

                // 获取第二个输入框的文本
                textLength = GetWindowTextLengthW(hTextBox2);
                buffer = new wchar_t[textLength + 1];
                GetWindowTextW(hTextBox2, buffer, textLength + 1);
                phoneNumber = wstring2string(buffer);
                delete[] buffer;

                // 获取第三个输入框的文本
                textLength = GetWindowTextLengthW(hTextBox3);
                buffer = new wchar_t[textLength + 1];
                GetWindowTextW(hTextBox3, buffer, textLength + 1);
                email = wstring2string(buffer);
                delete[] buffer;
                manager.addContact(name, phoneNumber, category, email);
            }
            break;
            case IDM_DELETE:
            {
                int textLength = GetWindowTextLengthW(hTextBox1);
				wchar_t* buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox1, buffer, textLength + 1);
				string name = wstring2string(buffer);
				delete[] buffer;
				DestroyWindow(hTextBox1);
				DestroyWindow(hButton1);
				manager.deleteContact(name);
            }
            break;
            case IDM_MODIFY: {
                int textLength = GetWindowTextLengthW(hTextBox1);
                wchar_t* buffer = new wchar_t[textLength + 1];
                GetWindowTextW(hTextBox1, buffer, textLength + 1);
                string name = wstring2string(buffer);
                delete[] buffer;

                 textLength = GetWindowTextLengthW(hTextBox2);
                 buffer = new wchar_t[textLength + 1];
                GetWindowTextW(hTextBox2, buffer, textLength + 1);
                string phoneNumber = wstring2string(buffer);
                delete[] buffer;

                manager.modifyContact(name,phoneNumber);
            }break;
            case IDM_DIAL:
            {
                int textLength = GetWindowTextLengthW(hTextBox1);
                wchar_t* buffer = new wchar_t[textLength + 1];
                GetWindowTextW(hTextBox1, buffer, textLength + 1);
                string name = wstring2string(buffer);
                delete[] buffer;
                
                string phoneNumber=manager.dialContact(name);

                HWND hSecondPage1 = CreateWindowW(szWindowClass, L"拨号中", WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
                ShowWindow(hSecondPage1, SW_SHOW);
                HWND label = CreateWindowW(L"STATIC", L"拨号中...\n", WS_CHILD | WS_VISIBLE,
                    100, 100, 500, 500, hSecondPage1, NULL, hInst, NULL);
                //以打字机的方式逐个将phoneNumber中的字符追加到label中
                for (int i = 0; i < phoneNumber.length(); i++) {
                    Sleep(1000);
                    wchar_t temp[2] = { phoneNumber[i], '\0' };

                    MessageBeep(MB_OK);
                    // 获取当前标签控件的文本长度
                    int textLength = SendMessage(label, WM_GETTEXTLENGTH, 0, 0);

                    // 为新文本分配内存，并将原有文本复制到新内存中
                    wchar_t* newText = new wchar_t[textLength + 2];
                    SendMessage(label, WM_GETTEXT, textLength + 1, (LPARAM)newText);

                    // 追加新字符到新文本末尾
                    newText[textLength] = temp[0];
                    newText[textLength + 1] = '\0';

                    // 设置标签控件的新文本
                    SendMessage(label, WM_SETTEXT, 0, (LPARAM)newText);

                    // 释放内存
                    delete[] newText;
                }
                Sleep(1000);
                ShowWindow(hSecondPage1, SW_HIDE);




            }break;
            }
            DestroyWindow(hTextBox1);
            DestroyWindow(hTextBox2);
            DestroyWindow(hTextBox3);
            DestroyWindow(hlabel1);
            DestroyWindow(hlabel2);
            DestroyWindow(hlabel3);
            DestroyWindow(hOfficialRadioButton);
            DestroyWindow(hIndividualRadioButton);
            DestroyWindow(hBusinessRadioButton);
            DestroyWindow(hButton1);
            fresh_list();
        }
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
