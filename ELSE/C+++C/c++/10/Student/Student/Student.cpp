﻿

#include "framework.h"
#include "Student.h"
#include <bits/stdc++.h>
#include <CommCtrl.h>

using namespace std;
// 将wstring转换成string
int choice_class, choice_sort;
void fresh_list();
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
// 学生信息结构体
struct Student
{
    string name;
    string id;
    int chinese;
    int math;
    int english;
};
vector<Student> students;


vector<Student> read_student_file(vector<Student>& students)
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
            return students;
        }

        std::string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            std::string name, id;
            std::string dummy;
            int chinese, math, english;
            if (!(iss >> name >> dummy >> id >> dummy >> chinese >> dummy >> math >> dummy >> english))
            {
                std::cerr << "Error: invalid student file format" << std::endl;
                return students;
            }
            students.push_back({ name, id, chinese, math, english });
        }
        infile.close();
    }
    return students;
}

// 写入学生信息文件
void write_student_file(string filename, vector<Student>& students)
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error: can't open file " << filename << endl;
        return;
    }

    for (const auto& s : students)
    {
        outfile << s.name << " , " << s.id << " , " << s.chinese << " , " << s.math << " , " << s.english << endl;
    }

    outfile.close();
}

// 根据姓名查找学生
vector<Student> find_student_by_name(vector<Student>& students, string name)
{
    vector<Student> result;
    for (const auto& s : students)
    {
        if (s.name == name)
        {
            result.push_back(s);
        }
    }
    return result;
}
// 根据学号查找学生
Student* find_student_by_id(vector<Student>& students, string id)
{
    for (const auto& s : students)
    {
        if (s.id == id)
        {
            return (Student*)&s;
        }
    }
    return NULL;
}
// 添加学生信息
void add_student(vector<Student>& students)
{
    string name, id;
    int chinese, math, english;
    cout << "Enter student name: ";
    cin >> name;
    cout << "Enter student id: ";
    cin >> id;
    cout << "Enter Chinese score: ";
    cin >> chinese;
    cout << "Enter Math score: ";
    cin >> math;
    cout << "Enter English score: ";
    cin >> english;
    students.push_back({ name, id, chinese, math, english });
    cout << "Student " << name << " added." << endl;
}
// 删除学生信息
void delete_student(vector<Student>& students, string id)
{
    cout << "Enter student id: ";
    // cin >> id;
    std::vector<Student>::iterator it = remove_if(students.begin(), students.end(), [id](const Student& s)
        { return s.id == id; });
    if (it != students.end())
    {
        students.erase(it, students.end());
        cout << "Student " << id << " deleted." << endl;
    }
    else
    {
        cout << "Error: student " << id << " not found." << endl;
    }
}
// 修改学生信息
void modify_student(vector<Student>& students)
{
    string id;
    cout << "Enter student id: ";
    cin >> id;
    auto s = find_student_by_id(students, id);
    if (s == nullptr)
    {
        cout << "Error: student " << id << " not found." << endl;
        return;
    }
    // 修改学生信息
    int chinese, math, english;
    cout << "Enter Chinese score [" << s->chinese << "]: ";
    cin >> chinese;
    cout << "Enter Math score [" << s->math << "]: ";
    cin >> math;
    cout << "Enter English score [" << s->english << "]: ";
    cin >> english;
    if (chinese != -1)
    {
        s->chinese = chinese;
    }
    if (math != -1)
    {
        s->math = math;
    }
    if (english != -1)
    {
        s->english = english;
    }
    cout << "Student " << s->name << " modified." << endl;
}
void score_statistics(vector<Student>& students)
{
    string course;
    int low, high;
    cout << "Enter course name: ";
    cin >> course;
    cout << "Enter score range [low high]: ";
    cin >> low >> high;
    int count = 0;
    for (const Student& s : students)
    {
        int score;
        if (course == "Chinese")
        {
            score = s.chinese;
        }
        else if (course == "Math")
        {
            score = s.math;
        }
        else if (course == "English")
        {
            score = s.english;
        }
        else
        {
            cout << "Error: invalid course name." << endl;
            return;
        }

        if (score >= low && score <= high)
        {
            count++;
        }
    }

    cout << "There are " << count << " students with " << course << " scores between " << low << " and " << high << "." << endl;
}
void sort_students(vector<Student>& students)
{
    string course;
    int order;
    cout << "Enter course name: ";
    cin >> course;
    cout << "Enter sort order (0 for ascending, 1 for descending): ";
    cin >> order; // 按成绩排序
    if (course == "Chinese")
    {
        if (order == 0)
        {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                { return a.chinese < b.chinese; });
        }
        else
        {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                { return a.chinese > b.chinese; });
        }
    }
    else if (course == "Math")
    {
        if (order == 0)
        {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                { return a.math < b.math; });
        }
        else
        {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                { return a.math > b.math; });
        }
    }
    else if (course == "English")
    {
        if (order == 0)
        {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                { return a.english < b.english; });
        }
        else
        {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                { return a.english > b.english; });
        }
    }
    else
    {
        cout << "Error: invalid course name." << endl;
        return;
    }

    // 输出排序结果
    cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
    for (const Student& s : students)
    {
        // 输出学生信息
        cout << s.name << "\t" << s.id << "\t" << s.chinese << "\t" << s.math << "\t" << s.english << endl;
    }
}
// 计算平均分
void average_score(vector<Student>& students)
{
    string course;
    cout << "Enter course name: ";
    cin >> course;
    double sum = 0;
    for (const Student& s : students)
    {
        int score;
        if (course == "Chinese")
        {
            score = s.chinese;
        }
        else if (course == "Math")
        {
            score = s.math;
        }
        else if (course == "English")
        {
            score = s.english;
        }
        else
        {
            cout << "Error: invalid course name." << endl;
            return;
        }
        sum += score;
    }
    cout << "The average score of " << course << " is " << sum / students.size() << "." << endl;
}
void search_students(vector<Student>& students)
{
    int choice = 0;
    cout << "1. Search by name" << endl;
    cout << "2. Search by id" << endl;
    cout << "Enter your choice [1-2]: ";
    cin >> choice;
    if (choice == 1)
    {
        string name;
        cout << "Enter student name: ";
        cin >> name;
        vector<Student> result = find_student_by_name(students, name);
        if (result.empty())
        {
            cout << "Error: student " << name << " not found." << endl;
            return;
        }
        // 输出学生信息
        cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
        for (const auto& s : result)
        {
            cout << s.name << "\t" << s.id << "\t" << s.chinese << "\t" << s.math << "\t" << s.english << endl;
        }
    }
    else if (choice == 2)
    {
        string id;
        cout << "Enter student id: ";
        cin >> id;
        Student* s = find_student_by_id(students, id);
        if (s == NULL)
        {
            cout << "Error: student " << id << " not found." << endl;
            return;
        }
        // 输出学生信息
        cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
        cout << s->name << "\t" << s->id << "\t" << s->chinese << "\t" << s->math << "\t" << s->english << endl;
    }
    else
    {
        cout << "Error: invalid choice." << endl;
    }
}
void show_all_students(vector<Student>& students)
{
    // 输出学生信息
    cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
    for (const auto& s : students)
    {
        cout << s.name << "\t" << s.id << "\t" << s.chinese << "\t" << s.math << "\t" << s.english << endl;
    }
}

// 此代码模块中包含的函数的前向声明:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    //read_student_file(students);
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_STUDENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STUDENT));

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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STUDENT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_STUDENT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hMainPage = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hMainPage)
    {
        return FALSE;
    }

    hListView = CreateWindowW(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 500,500, hMainPage, nullptr, hInstance, nullptr);
    // 设置列表视图控件样式
    ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT);

    // 添加列表视图控件的列
    LVCOLUMN lvColumn;
    lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
    lvColumn.cx = 100;

    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        lvColumn.pszText = const_cast<wchar_t*>(columnHeaders[i]);
        ListView_InsertColumn(hListView, i, &lvColumn);
    }
    fresh_list();
    // 创建9个按钮
    hButton1 = CreateWindowW(L"BUTTON", L"添加学生", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        600, 50, 100, 30, hMainPage, (HMENU)1, hInstance, NULL);
    hButton2 = CreateWindowW(L"BUTTON", L"删除学生", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        700, 50, 100, 30, hMainPage, (HMENU)2, hInstance, NULL);
    hButton3 = CreateWindowW(L"BUTTON", L"修改信息", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        800, 50, 100, 30, hMainPage, (HMENU)3, hInstance, NULL);
    hButton4 = CreateWindowW(L"BUTTON", L"搜索信息", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        600, 100, 100, 30, hMainPage, (HMENU)4, hInstance, NULL);
    hButton5 = CreateWindowW(L"BUTTON", L"成绩统计", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       700, 100, 100, 30, hMainPage, (HMENU)5, hInstance, NULL);
    hButton6 = CreateWindowW(L"BUTTON", L"学生排序", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        800, 100, 100, 30, hMainPage, (HMENU)6, hInstance, NULL);
    hButton7 = CreateWindowW(L"BUTTON", L"打开文件", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        600, 150, 100, 30, hMainPage, (HMENU)7, hInstance, NULL);
    hButton8 = CreateWindowW(L"BUTTON", L"统计均值", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        700, 150, 100, 30, hMainPage, (HMENU)8, hInstance, NULL);
    hButton9 = CreateWindowW(L"BUTTON", L"保存退出", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        800, 150, 100, 30, hMainPage, (HMENU)9, hInstance, NULL);
    hCurrentPage = hMainPage; // 设置当前页面为主窗口

    ShowWindow(hMainPage, nCmdShow);
    UpdateWindow(hMainPage);

    return TRUE;
}

void fresh_list()
{
    ListView_DeleteAllItems(hListView);
    for (int i = 0; i < students.size(); i++)
    {
        LVITEM lvItem;
        lvItem.mask = LVIF_TEXT;
        lvItem.iItem = i;
        lvItem.iSubItem = 0;
        wstring name = string2wstring(students[i].name);
        lvItem.pszText = &name[0]; // 插入姓名

        // 插入第一列的数据
        ListView_InsertItem(hListView, &lvItem);

        // 插入其他列的数据
        std::wstring chinese = std::to_wstring(students[i].chinese);
        std::wstring math = std::to_wstring(students[i].math);
        std::wstring english = std::to_wstring(students[i].english);

        lvItem.iSubItem = 1;
        std::wstring id = string2wstring(students[i].id);
        lvItem.pszText = &id[0]; // 插入学号
        ListView_SetItemText(hListView, i, 1, lvItem.pszText);

        lvItem.iSubItem = 2;
        lvItem.pszText = (LPWSTR)chinese.c_str(); // 插入语文成绩
        ListView_SetItemText(hListView, i, 2, lvItem.pszText);

        lvItem.iSubItem = 3;
        lvItem.pszText = (LPWSTR)math.c_str(); // 插入数学成绩
        ListView_SetItemText(hListView, i, 3, lvItem.pszText);

        lvItem.iSubItem = 4;
        lvItem.pszText = (LPWSTR)english.c_str(); // 插入英语成绩
        ListView_SetItemText(hListView, i, 4, lvItem.pszText);
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
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case 1: // 处理按钮1的点击事件
        {
            // 创建第二个页面窗口
            hSecondPage1 = CreateWindowW(szWindowClass, L"添加学生", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);

            // 隐藏当前页面并显示第二个页面
            ShowWindow(hCurrentPage, SW_HIDE);
            ShowWindow(hSecondPage1, SW_SHOW);

            HWND hLabel1 = CreateWindowW(L"STATIC", L"姓名:", WS_CHILD | WS_VISIBLE, 150, 50, 100, 20, hSecondPage1, NULL, hInst, NULL);
            HWND hLabel2 = CreateWindowW(L"STATIC", L"ID:", WS_CHILD | WS_VISIBLE, 150, 80, 100, 20, hSecondPage1, NULL, hInst, NULL);
            HWND hLabel3 = CreateWindowW(L"STATIC", L"语文:", WS_CHILD | WS_VISIBLE, 150, 110, 100, 20, hSecondPage1, NULL, hInst, NULL);
            HWND hLabel4 = CreateWindowW(L"STATIC", L"数学:", WS_CHILD | WS_VISIBLE, 150, 140, 100, 20, hSecondPage1, NULL, hInst, NULL);
            HWND hLabel5 = CreateWindowW(L"STATIC", L"英语:", WS_CHILD | WS_VISIBLE, 150, 170, 100, 20, hSecondPage1, NULL, hInst, NULL);

            hTextBoxa1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 50, 200, 20, hSecondPage1, NULL, hInst, NULL);
            hTextBoxa2 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 80, 200, 20, hSecondPage1, NULL, hInst, NULL);
            hTextBoxa3 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 110, 200, 20, hSecondPage1, NULL, hInst, NULL);
            hTextBoxa4 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 140, 200, 20, hSecondPage1, NULL, hInst, NULL);
            hTextBoxa5 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 170, 200, 20, hSecondPage1, NULL, hInst, NULL);
            // 创建提交按钮
            hSubmitButton = CreateWindowW(L"BUTTON", L"确认", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 150, 100, 30, hSecondPage1, (HMENU)11, hInst, NULL);
            // 创建返回按钮
            hReturnButton = CreateWindowW(L"BUTTON", L"返回", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 50, 100, 30, hSecondPage1, (HMENU)10, hInst, NULL);

            // 更新当前页面变量为第二个页面
            hCurrentPage = hSecondPage1;
        }
        break;
        case 2:
        {
            // 创建第二个页面窗口
            hSecondPage2 = CreateWindowW(szWindowClass, L"删除学生", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
            HWND hLabel1 = CreateWindowW(L"STATIC", L"ID：", WS_CHILD | WS_VISIBLE, 50, 90, 20, 20, hSecondPage2, NULL, hInst, NULL);
            hTextBoxa1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                70, 90, 80, 20, hSecondPage2, NULL, hInst, NULL);
            hSubmitButton = CreateWindowW(L"BUTTON", L"确认", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 150, 100, 30, hSecondPage2, (HMENU)12, hInst, NULL);
            // 隐藏当前页面并显示第二个页面
            ShowWindow(hCurrentPage, SW_HIDE);
            ShowWindow(hSecondPage2, SW_SHOW);

            // 创建返回按钮
            hReturnButton = CreateWindowW(L"BUTTON", L"返回", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 50, 100, 30, hSecondPage2, (HMENU)10, hInst, NULL);

            // 更新当前页面变量为第二个页面
            hCurrentPage = hSecondPage2;
        }
        break;
        case 3:
        {
            // 创建第二个页面窗口
            hSecondPage3 = CreateWindowW(szWindowClass, L"修改信息", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
            hTextBoxa1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 50, 200, 20, hSecondPage3, NULL, hInst, NULL);
            HWND hLabel1 = CreateWindowW(L"STATIC", L"ID：", WS_CHILD | WS_VISIBLE, 150, 50, 50, 20, hSecondPage3, NULL, hInst, NULL);
            hTextBoxa2 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 80, 200, 20, hSecondPage3, NULL, hInst, NULL);
            HWND hLabel2 = CreateWindowW(L"STATIC", L"语文：", WS_CHILD | WS_VISIBLE, 150, 80, 50, 20, hSecondPage3, NULL, hInst, NULL);
            hTextBoxa3 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 110, 200, 20, hSecondPage3, NULL, hInst, NULL);
            HWND hLabel3 = CreateWindowW(L"STATIC", L"数学：", WS_CHILD | WS_VISIBLE, 150, 110, 50, 20, hSecondPage3, NULL, hInst, NULL);
            hTextBoxa4 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                200, 140, 200, 20, hSecondPage3, NULL, hInst, NULL);
            HWND hLabel4 = CreateWindowW(L"STATIC", L"英语：", WS_CHILD | WS_VISIBLE, 150, 140, 50, 20, hSecondPage3, NULL, hInst, NULL);

            hSubmitButton = CreateWindowW(L"BUTTON", L"确认", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 150, 100, 30, hSecondPage3, (HMENU)13, hInst, NULL);
            // 隐藏当前页面并显示第二个页面
            ShowWindow(hCurrentPage, SW_HIDE);
            ShowWindow(hSecondPage3, SW_SHOW);

            // 创建返回按钮
            hReturnButton = CreateWindowW(L"BUTTON", L"返回", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 50, 100, 30, hSecondPage3, (HMENU)10, hInst, NULL);

            // 更新当前页面变量为第二个页面
            hCurrentPage = hSecondPage3;
        }
        break;
        case 4:
        {
            // 创建第二个页面窗口
            hSecondPage4 = CreateWindowW(szWindowClass, L"Second Page", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
            HWND hLabel1 = CreateWindowW(L"STATIC", L"ID/姓名：", WS_CHILD | WS_VISIBLE, 50, 80, 100, 20, hSecondPage4, NULL, hInst, NULL);
            hTextBoxa1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                50, 110, 100, 20, hSecondPage4, NULL, hInst, NULL);

            hSubmitButton1 = CreateWindowW(L"BUTTON", L"姓名查询", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 150, 100, 30, hSecondPage4, (HMENU)14, hInst, NULL);
            hSubmitButton2 = CreateWindowW(L"BUTTON", L"ID查询", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 200, 100, 30, hSecondPage4, (HMENU)15, hInst, NULL);
            // 隐藏当前页面并显示第二个页面
            ShowWindow(hCurrentPage, SW_HIDE);
            ShowWindow(hSecondPage4, SW_SHOW);

            // 创建返回按钮
            hReturnButton = CreateWindowW(L"BUTTON", L"返回", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 50, 100, 30, hSecondPage4, (HMENU)10, hInst, NULL);

            // 更新当前页面变量为第二个页面
            hCurrentPage = hSecondPage4;
        }
        break;
        case 5:
        {
            // 创建第二个页面窗口
            hSecondPage5 = CreateWindowW(szWindowClass, L"Second Page", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);

            hButton1 = CreateWindowW(L"BUTTON", L"语文", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 150, 100, 30, hSecondPage5, (HMENU)16, hInst, NULL);
            hButton2 = CreateWindowW(L"BUTTON", L"数学", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 200, 100, 30, hSecondPage5, (HMENU)17, hInst, NULL);
            hButton3 = CreateWindowW(L"BUTTON", L"英语", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 250, 100, 30, hSecondPage5, (HMENU)18, hInst, NULL);
            HWND hLabel1 = CreateWindowW(L"STATIC", L"最小", WS_CHILD | WS_VISIBLE, 50, 90, 50, 20, hSecondPage5, NULL, hInst, NULL);
            HWND hLabel2 = CreateWindowW(L"STATIC", L"最大", WS_CHILD | WS_VISIBLE, 100, 90, 50, 20, hSecondPage5, NULL, hInst, NULL);

            hTextBoxa3 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                50, 110, 50, 20, hSecondPage5, NULL, hInst, NULL);
            hTextBoxa4 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
                100, 110, 50, 20, hSecondPage5, NULL, hInst, NULL);
            // 隐藏当前页面并显示第二个页面
            ShowWindow(hCurrentPage, SW_HIDE);
            ShowWindow(hSecondPage5, SW_SHOW);

            // 创建返回按钮
            hReturnButton = CreateWindowW(L"BUTTON", L"返回", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 50, 100, 30, hSecondPage5, (HMENU)10, hInst, NULL);

            // 更新当前页面变量为第二个页面
            hCurrentPage = hSecondPage5;
        }
        break;
        case 6:
        {
            // 创建第二个页面窗口
            hSecondPage6 = CreateWindowW(szWindowClass, L"学生排序", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);

            // 创建 Chinese 单选按钮
            hChineseRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"语文",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                200, 50, 100, 30,
                hSecondPage6,
                (HMENU)30, // 修改为不同的标识符
                hInst,
                NULL);

            // 创建 Math 单选按钮
            hMathRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"数学",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                200, 80, 100, 30,
                hSecondPage6,
                (HMENU)31, // 修改为不同的标识符
                hInst,
                NULL);

            // 创建 English 单选按钮
            hEnglishRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"英语",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                200, 110, 100, 30,
                hSecondPage6,
                (HMENU)32, // 修改为不同的标识符
                hInst,
                NULL);

            // 创建 Ascending 单选按钮
            hAscendingRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"升序",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                200, 150, 100, 30,
                hSecondPage6,
                (HMENU)40, // 修改为不同的标识符
                hInst,
                NULL);

            // 创建 Descending 单选按钮
            hDescendingRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"降序",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                200, 180, 100, 30,
                hSecondPage6,
                (HMENU)41, // 修改为不同的标识符
                hInst,
                NULL);

            hSubmitButton = CreateWindowW(L"BUTTON", L"确认", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 150, 100, 30, hSecondPage6, (HMENU)19, hInst, NULL);
            // 隐藏当前页面并显示第二个页面
            ShowWindow(hCurrentPage, SW_HIDE);
            ShowWindow(hSecondPage6, SW_SHOW);

            // 创建返回按钮
            hReturnButton = CreateWindowW(L"BUTTON", L"返回", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 50, 100, 30, hSecondPage6, (HMENU)10, hInst, NULL);

            // 更新当前页面变量为第二个页面
            hCurrentPage = hSecondPage6;
        }
        break;
        case 7:
        {
            read_student_file(students);
            fresh_list();
        }
        break;
        case 8:
        {
            // 创建第二个页面窗口
            hSecondPage8 = CreateWindowW(szWindowClass, L"Second Page", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
            // 创建 Chinese 单选按钮
            hChineseRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"语文",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                200, 50, 100, 30,
                hSecondPage8,
                (HMENU)33, // 修改为不同的标识符
                hInst,
                NULL);

            // 创建 Math 单选按钮
            hMathRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"数学",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                200, 80, 100, 30,
                hSecondPage8,
                (HMENU)34, // 修改为不同的标识符
                hInst,
                NULL);

            // 创建 English 单选按钮
            hEnglishRadioButton = CreateWindowEx(
                0,
                L"BUTTON",
                L"英语",
                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                200, 110, 100, 30,
                hSecondPage8,
                (HMENU)35, // 修改为不同的标识符
                hInst,
                NULL);
            // 创建返回按钮
            hReturnButton = CreateWindowW(L"BUTTON", L"返回", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 50, 100, 30, hSecondPage8, (HMENU)10, hInst, NULL);

            hSubmitButton = CreateWindowW(L"BUTTON", L"确认", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 150, 100, 30, hSecondPage8, (HMENU)20, hInst, NULL);

            // 隐藏当前页面并显示第二个页面
            ShowWindow(hCurrentPage, SW_HIDE);
            ShowWindow(hSecondPage8, SW_SHOW);
            // 更新当前页面变量为第二个页面
            hCurrentPage = hSecondPage8;
        }
        break;
        case 9:
        {
            write_student_file("students.txt", students);
            MessageBox(hSecondPage8, L"修改已保存，点击确认后退出", L"提示", MB_OK);
            exit(0);
        }
        break;
        case 10:
        {
            // 隐藏当前页面并显示主窗口
            ShowWindow(hCurrentPage, SW_HIDE);
            ShowWindow(hMainPage, SW_SHOW);

            // 更新当前页面变量为主窗口
            hCurrentPage = hMainPage;
            fresh_list();
            // 销毁返回按钮
            DestroyWindow(hReturnButton);
        }
        break;
        case 11: // 处理sub按钮的点击事件
        {
            // 获取第一个输入框的文本
            int textLength = GetWindowTextLengthW(hTextBoxa1);
            wchar_t* buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa1, buffer, textLength + 1);
            std::wstring inputText1 = buffer;
            delete[] buffer;

            // 获取第二个输入框的文本
            textLength = GetWindowTextLengthW(hTextBoxa2);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa2, buffer, textLength + 1);
            std::wstring inputText2 = buffer;
            delete[] buffer;

            // 获取第三个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa3);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa3, buffer, textLength + 1);
            int inputValue3 = _wtoi(buffer);
            delete[] buffer;

            // 获取第四个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa4);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa4, buffer, textLength + 1);
            int inputValue4 = _wtoi(buffer);
            delete[] buffer;

            // 获取第五个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa5);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa5, buffer, textLength + 1);
            int inputValue5 = _wtoi(buffer);
            delete[] buffer;

            // 创建保存的消息文本
            std::wstring messageText = L"信息已保存：\n";
            messageText += L"姓名: " + inputText1 + L"\n";
            messageText += L"ID: " + inputText2 + L"\n";
            messageText += L"语文: " + std::to_wstring(inputValue3) + L"\n";
            messageText += L"数学: " + std::to_wstring(inputValue4) + L"\n";
            messageText += L"英语: " + std::to_wstring(inputValue5);

            // 显示消息框
            MessageBoxW(hCurrentPage, messageText.c_str(), L"Saved Data", MB_OK);

            students.push_back({ wstring2string(inputText1), wstring2string(inputText2), inputValue3, inputValue4, inputValue5 });

            fresh_list();
        }
        break;
        case 12:
        {
            int textLength = GetWindowTextLengthW(hTextBoxa1);
            wchar_t* buffer = new wchar_t[textLength + 1];
            textLength = GetWindowTextLengthW(hTextBoxa1);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa1, buffer, textLength + 1);
            std::wstring inputText2 = buffer;
            delete[] buffer;
            delete_student(students, wstring2string(inputText2));
            fresh_list();
        }
        break;
        case 13:
        {
            int textLength = GetWindowTextLengthW(hTextBoxa1);
            wchar_t* buffer = new wchar_t[textLength + 1];
            textLength = GetWindowTextLengthW(hTextBoxa1);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa1, buffer, textLength + 1);
            std::wstring id = buffer;
            delete[] buffer;
            auto s = find_student_by_id(students, wstring2string(id));
            if (s == nullptr)
            {
                cout << "Error: student " << wstring2string(id) << " not found." << endl;
                break;
            }
            // 获取第二个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa2);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa2, buffer, textLength + 1);
            int chinese = _wtoi(buffer);
            delete[] buffer;

            // 获取第三个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa3);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa3, buffer, textLength + 1);
            int math = _wtoi(buffer);
            delete[] buffer;

            // 获取第四个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa4);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa4, buffer, textLength + 1);
            int english = _wtoi(buffer);
            delete[] buffer;
            if (chinese != -1)
            {
                s->chinese = chinese;
            }
            if (math != -1)
            {
                s->math = math;
            }
            if (english != -1)
            {
                s->english = english;
            }
            cout << "Student " << s->name << " modified." << endl;
            fresh_list();
        }
        break;
        case 14:
        {
            int textLength = GetWindowTextLengthW(hTextBoxa1);
            wchar_t* buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa1, buffer, textLength + 1);
            std::wstring inputText1 = buffer;
            delete[] buffer;
            string name = wstring2string(inputText1);
            cout << "Enter student name: ";
            vector<Student> result = find_student_by_name(students, name);
            if (result.empty())
            {
                cout << "Error: student " << name << " not found." << endl;
                break;
            }
            // 输出学生信息
            // 创建保存的消息文本
            string messageText = "Name\tID\tChinese\tMath\tEnglish\n";
            for (const auto& s : result)
            {
                messageText += s.name + "\t" + s.id + "\t" + to_string(s.chinese) + "\t" + to_string(s.math) + "\t" + to_string(s.english) + "\n";
            }

            // 显示消息框
            // 创建标签
            HWND hLabel = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE,
                500, 50, 2000, 3000,
                hSecondPage4,
                NULL,
                hInst,
                NULL);
            SetWindowText(hLabel, string2wstring(messageText).c_str());
            cout << "Name\tID\tChinese\tMath\tEnglish" << endl;
        }
        break;
        case 15:
        {
            int textLength = GetWindowTextLengthW(hTextBoxa1);
            wchar_t* buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa1, buffer, textLength + 1);
            std::wstring inputText1 = buffer;
            delete[] buffer;
            string id = wstring2string(inputText1);
            cout << "Enter student name: ";
            Student* result = find_student_by_id(students, id);
            if (result == NULL)
            {
                cout << "Error: student " << id << " not found." << endl;
                break;
            }
            // 输出学生信息
            // 创建保存的消息文本
            string messageText = "Name\tID\tChinese\tMath\tEnglish\n";
            messageText += result->name + "\t" + result->id + "\t" + to_string(result->chinese) + "\t" + to_string(result->math) + "\t" + to_string(result->english) + "\n";

            // 显示消息框
            // 创建标签
            HWND hLabel = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE,
                500, 50, 2000, 3000,
                hSecondPage4,
                NULL,
                hInst,
                NULL);
            SetWindowText(hLabel, string2wstring(messageText).c_str());
        }
        break;
        case 16:
        {
            int count = 0;
            // 获取第三个输入框的整数
            int textLength = GetWindowTextLengthW(hTextBoxa3);
            wchar_t* buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa3, buffer, textLength + 1);
            int low = _wtoi(buffer);
            delete[] buffer;

            // 获取第四个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa4);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa4, buffer, textLength + 1);
            int high = _wtoi(buffer);
            delete[] buffer;
            for (const Student& s : students)
            {
                int score = s.chinese;
                if (score >= low && score <= high)
                {
                    count++;
                }
            }
            string messageText = "总共有" + to_string(count) + "个学生的语文成绩在" + to_string(low) + "和" + to_string(high) + "之间";
            // 显示消息框
            // 创建标签
            HWND hLabel = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE,
                500, 50, 2000, 3000,
                hSecondPage5,
                NULL,
                hInst,
                NULL);
            SetWindowText(hLabel, string2wstring(messageText).c_str());
        }
        break;
        case 17:
        {
            int count = 0;
            // 获取第三个输入框的整数
            int textLength = GetWindowTextLengthW(hTextBoxa3);
            wchar_t* buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa3, buffer, textLength + 1);
            int low = _wtoi(buffer);
            delete[] buffer;

            // 获取第四个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa4);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa4, buffer, textLength + 1);
            int high = _wtoi(buffer);
            delete[] buffer;
            for (const Student& s : students)
            {
                int score = s.math;
                if (score >= low && score <= high)
                {
                    count++;
                }
            }
            string messageText = "总共有" + to_string(count) + "个学生的数学成绩在" + to_string(low) + "和" + to_string(high) + "之间";
            // 显示消息框
            // 创建标签
            HWND hLabel = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE,
                500, 50, 2000, 3000,
                hSecondPage5,
                NULL,
                hInst,
                NULL);
            SetWindowText(hLabel, string2wstring(messageText).c_str());
        }
        break;
        case 18:
        {
            int count = 0;
            // 获取第三个输入框的整数
            int textLength = GetWindowTextLengthW(hTextBoxa3);
            wchar_t* buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa3, buffer, textLength + 1);
            int low = _wtoi(buffer);
            delete[] buffer;

            // 获取第四个输入框的整数
            textLength = GetWindowTextLengthW(hTextBoxa4);
            buffer = new wchar_t[textLength + 1];
            GetWindowTextW(hTextBoxa4, buffer, textLength + 1);
            int high = _wtoi(buffer);
            delete[] buffer;
            for (const Student& s : students)
            {
                int score = s.english;
                if (score >= low && score <= high)
                {
                    count++;
                }
            }
            string messageText = "总共有" + to_string(count) + "个学生的英语成绩在" + to_string(low) + "和" + to_string(high) + "之间";
            // 显示消息框
            // 创建标签
            HWND hLabel = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE,
                500, 50, 2000, 3000,
                hSecondPage5,
                NULL,
                hInst,
                NULL);
            SetWindowText(hLabel, string2wstring(messageText).c_str());
        }
        break;
        case 19:
        {
            if (choice_class == 0)
            {
                if (choice_sort == 0)
                {
                    sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                        { return a.chinese < b.chinese; });
                }
                else
                {
                    sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                        { return a.chinese > b.chinese; });
                }
            }
            else if (choice_class == 1)
            {
                if (choice_sort == 0)
                {
                    sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                        { return a.math < b.math; });
                }
                else
                {
                    sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                        { return a.math > b.math; });
                }
            }
            else
            {
                if (choice_sort == 0)
                {
                    sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                        { return a.english < b.english; });
                }
                else
                {
                    sort(students.begin(), students.end(), [](const Student& a, const Student& b)
                        { return a.english > b.english; });
                }
            }
        }
        break;
        case 20:
        {
            string course = choice_class == 0 ? "语文" : choice_class == 1 ? "数学" : "英语";
            cout << "Enter course name: ";
            //cin >> course;
            double sum = 0;
            for (const Student& s : students)
            {
                int score;
                if (choice_class == 0)
                {
                    score = s.chinese;
                }
                else if (choice_class == 1)
                {
                    score = s.math;
                }
                else if (choice_class == 2)
                {
                    score = s.english;
                }
                else
                {
                    cout << "Error: invalid course name." << endl;
                    break;
                }
                sum += score;
            }
            cout << "The average score of " << course << " ： " << sum / students.size() << "." << endl;

            string messageText = "平均分 " + course + " ： " + to_string(sum / students.size()) + ".";

            // 显示消息框
            // 创建标签
            HWND hLabel = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE,
                500, 50, 2000, 3000,
                hSecondPage8,
                NULL,
                hInst,
                NULL);
            SetWindowText(hLabel, string2wstring(messageText).c_str());
        }
        break;
        case 30:
        {
            choice_class = 0;
        }
        break;
        case 31:
        {
            choice_class = 1;
        }
        break;
        case 32:
        {
            choice_class = 2;
        }
        break;
        case 33:
        {
            choice_class = 0;
        }
        break;
        case 34:
        {
            choice_class = 1;
        }
        break;
        case 35:
        {
            choice_class = 2;
        }
        break;
        case 40:
        {
            choice_sort = 0;
        }
        break;

        case 41:
        {
            choice_sort = 1;
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

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}