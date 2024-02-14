// AddressBook.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "StudentScore.h"

using namespace std;

// 加载数据
void loadData(string f1,string f2) {
	ifstream studentFile(f1);
	ifstream scoreFile(f2);

	if (!studentFile.is_open() || !scoreFile.is_open()) {
		cout << "无法打开文件。" << endl;
		return;
	}

	// 加载学生基本信息
	while (!studentFile.eof()) {
		StudentInfo student;
		studentFile >> student.studentID >> student.name >> student.gender >> student.dormitory >> student.phoneNumber;
		if (student.studentID == "")break;
		students.push_back(student);
	}

	// 加载学生成绩信息
	while (!scoreFile.eof()) {
		StudentScore score;
		scoreFile >> score.studentID >> score.courseCode >> score.courseName >> score.credit >> score.regularScore >> score.labScore >> score.examScore;
		if (score.studentID == "")break;
		if (score.labScore == -1) {
			score.compositeScore = score.regularScore * 0.3 + score.examScore * 0.7;
		}
		else {
			score.compositeScore = score.regularScore * 0.15 + score.labScore * 0.15 + score.examScore * 0.7;
		}

		scores.push_back(score);
	}
	studentFile.close();
	scoreFile.close();
}

// 保存数据
void saveData() {
	ofstream studentFile(f1);
	ofstream scoreFile(f2);

	if (!studentFile.is_open() || !scoreFile.is_open()) {
		cout << "无法保存数据到文件。" << endl;
		return;
	}

	// 保存学生基本信息
	for (const auto& student : students) {
		studentFile << student.studentID << " " << student.name << " " << student.gender << " " << student.dormitory << " " << student.phoneNumber << endl;
	}

	// 保存学生成绩信息
	for (const auto& score : scores) {
		scoreFile << score.studentID << " " << score.courseCode << " " << score.courseName << " " << score.credit << " " << score.regularScore << " " << score.labScore << " " << score.examScore << endl;
	}

	studentFile.close();
	scoreFile.close();
}

// 录入数据
void inputData(string studentID, string courseCode, string courseName, int credit, int regularScore, int labScore, int examScore) {

	// 检查学号是否存在
	auto it = find_if(scores.begin(), scores.end(), [&studentID](const StudentScore& score) {
		return score.studentID == studentID;
		});

	//if (it != scores.end()) {
	//	cout << "该学生已存在，请输入其他学号。" << endl;
	//	return;
	//}

	StudentScore score;
	score.studentID = studentID;
	score.courseCode = courseCode;
	score.courseName = courseName;
	score.credit = credit;
	score.regularScore = regularScore;
	score.labScore = labScore;
	score.examScore = examScore;

	if (labScore == -1) {
		score.compositeScore = regularScore * 0.3 + examScore * 0.7;
	}
	else {
		score.compositeScore = regularScore * 0.15 + labScore * 0.15 + examScore * 0.7;
	}
	scores.push_back(score);
}

// 打印学生基本信息
string  printStudentInfo(const StudentInfo& student) {
	string res = "";
	res += "学号：" + student.studentID + " 姓名：" + student.name + " 性别：" + student.gender + " 宿舍号码：" + student.dormitory + " 电话号码：" + student.phoneNumber + "\n";
	//cout << "学号：" << student.studentID << " 姓名：" << student.name << " 性别：" << student.gender << " 宿舍号码：" << student.dormitory << " 电话号码：" << student.phoneNumber << endl;
	return res;
}

// 打印学生成绩信息
string printScoreInfo(const StudentScore& score) {
	//cout << "学号：" << score.studentID << " 课程编号：" << score.courseCode << " 课程名称：" << score.courseName << " 综合成绩：" << score.compositeScore << " 实得学分：" << score.credit << endl;
	string res = "";
	res += "学号：" + score.studentID + " 课程编号：" + score.courseCode + " 课程名称：" + score.courseName + " 综合成绩：" + to_string(score.compositeScore) + " 实得学分：" + to_string(score.credit) + "\n";
	return res;
}


// 学生基本情况查询
string searchStudentInfo(int choice, string StuID, string StuName) {
	string key;
	if (choice == 1) {
		//cout << "请输入学号：";
		key = StuID;
	}
	else if (choice == 2) {
		//cout << "请输入姓名：";
		key = StuName;
	}
	else {
		cout << "无效的选项。" << endl;
		return "";
	}

	bool found = false;
	string message = "";
	for (const auto& student : students) {
		if (choice == 1 && student.studentID == key) {
			message += printStudentInfo(student);
			found = true;
			break;
		}
		else if (choice == 2 && student.name == key) {
			message += printStudentInfo(student);
			found = true;
		}
	}

	if (!found) {
		cout << "未找到相关学生信息。" << endl;
	}
	return message;
}

// 成绩查询
string searchScoreInfo(string studentID) {
	//string studentID;
	//cout << "请输入学号：";
	//cin >> studentID;

	bool found = false;
	double totalCredits = 0.0;
	double totalCompositeScore = 0.0;

	string res = "";
	for (const auto& score : scores) {
		if (score.studentID == studentID) {
			res+=printScoreInfo(score);
			totalCredits += score.credit;
			totalCompositeScore += score.compositeScore;
			found = true;
		}
	}
	if (!found) {
		//cout << "未找到该学生的成绩信息。" << endl;
		res = "未找到该学生的成绩信息。";
	}
	else {
		//cout << "共修：" << scores.size() << " 科，实得总学分为：" << totalCredits << endl;
		res += "共修：" + to_string(scores.size()) + " 科，实得总学分为：" + to_string(totalCredits) + "\n";
	}
	return res;
}

// 删除学生信息
void deleteStudent(string studentID) {
	//string studentID;
	//cout << "请输入学号：";
	//cin >> studentID;

	// 删除学生基本信息
	students.erase(remove_if(students.begin(), students.end(), [&studentID](const StudentInfo& student) {
		return student.studentID == studentID;
		}), students.end());

	// 删除学生成绩信息
	scores.erase(remove_if(scores.begin(), scores.end(), [&studentID](const StudentScore& score) {
		return score.studentID == studentID;
		}), scores.end());
}

// 按综合成绩升序排序
bool compareByCompositeScore(const StudentScore& score1, const StudentScore& score2) {
	return score1.compositeScore < score2.compositeScore;
}

// 按实得学分升序排序
bool compareByCredit(const StudentScore& score1, const StudentScore& score2) {
	return score1.credit < score2.credit;
}

// 排序功能
void sortScores(int choice) {
	//int choice;
	//cout << "请选择排序方式：" << endl;
	//cout << "1. 按综合成绩升序排序" << endl;
	//cout << "2. 按实得学分升序排序" << endl;
	//cin >> choice;

	if (choice == 1) {
		sort(scores.begin(), scores.end(), compareByCompositeScore);
	}
	else if (choice == 2) {
		sort(scores.begin(), scores.end(), compareByCredit);
	}
	else {
		cout << "无效的选项。" << endl;
		return;
	}
	cout << "排序完成。" << endl;
}


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
// 全局变量:

// 此代码模块中包含的函数的前向声明:

string read_contact_file()
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
	GetOpenFileNameA(&ofn);
	string fname = ofn.lpstrFile;
	return fname;
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
	LoadStringW(hInstance, IDC_STUDENTSCORE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STUDENTSCORE));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STUDENTSCORE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_STUDENTSCORE);
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
	SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
	HWND hButton = CreateWindow(TEXT("button"), TEXT("数据录入"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 10, 100, 30, hWnd, (HMENU)IDM_ADD, hInstance, NULL);
	HWND hButton2 = CreateWindow(TEXT("button"), TEXT("信息查询"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 50, 100, 30, hWnd, (HMENU)IDM_STUSEARCH, hInstance, NULL);
	HWND hButton3 = CreateWindow(TEXT("button"), TEXT("成绩查询"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 90, 100, 30, hWnd, (HMENU)IDM_SCOSEARCH, hInstance, NULL);
	HWND hButton4 = CreateWindow(TEXT("button"), TEXT("删除信息"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 130, 100, 30, hWnd, (HMENU)IDM_DELETE, hInstance, NULL);
	HWND hButton5 = CreateWindow(TEXT("button"), TEXT("排序功能"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 170, 100, 30, hWnd, (HMENU)IDM_SORT, hInstance, NULL);
	HWND hButton6 = CreateWindow(TEXT("button"), TEXT("保存并退出"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 210, 100, 30, hWnd, (HMENU)IDM_EXIT, hInstance, NULL);
	HWND hButton7 = CreateWindow(TEXT("button"), TEXT("导入信息"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800, 250, 100, 30, hWnd, (HMENU)IDM_LOAD, hInstance, NULL);
	hListView1 = CreateWindowW(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 750, 400, hWnd, nullptr, hInstance, nullptr);
	// 设置列表视图控件样式
	ListView_SetExtendedListViewStyle(hListView1, LVS_EX_FULLROWSELECT);

	// 添加列表视图控件的列
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
	lvColumn.cx = 150;

	for (int i = 0; i < COLUMN_COUNT1; i++)
	{
		lvColumn.pszText = const_cast<wchar_t*>(columnHeaders1[i]);
		ListView_InsertColumn(hListView1, i, &lvColumn);
	}

	hListView2 = CreateWindowW(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 420, 1200, 400, hWnd, nullptr, hInstance, nullptr);
	// 设置列表视图控件样式
	ListView_SetExtendedListViewStyle(hListView2, LVS_EX_FULLROWSELECT);

	// 添加列表视图控件的列
	lvColumn;
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
	lvColumn.cx = 150;

	for (int i = 0; i < COLUMN_COUNT2; i++)
	{
		lvColumn.pszText = const_cast<wchar_t*>(columnHeaders2[i]);
		ListView_InsertColumn(hListView2, i, &lvColumn);
	}

	if (!hWnd)
	{
		return FALSE;
	}

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
	ListView_DeleteAllItems(hListView1);
	ListView_DeleteAllItems(hListView2);
	for (int i = 0; i < students.size(); i++)
	{
		LVITEM lvItem;
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		wstring studentID = string2wstring(students[i].studentID);
		lvItem.pszText = &studentID[0]; // 插入姓名

		// 插入第一列的数据
		ListView_InsertItem(hListView1, &lvItem);

		lvItem.iSubItem = 1;
		std::wstring name = string2wstring(students[i].name);
		lvItem.pszText = &name[0]; // 插入电话
		ListView_SetItemText(hListView1, i, 1, lvItem.pszText);

		lvItem.iSubItem = 2;
		std::wstring gender = string2wstring(students[i].gender);
		lvItem.pszText = &gender[0]; // 插入学号
		ListView_SetItemText(hListView1, i, 2, lvItem.pszText);

		lvItem.iSubItem = 3;
		std::wstring dormitory = string2wstring(students[i].dormitory);
		lvItem.pszText = &dormitory[0]; // 插入学号
		ListView_SetItemText(hListView1, i, 3, lvItem.pszText);

		lvItem.iSubItem = 4;
		std::wstring phoneNumber = string2wstring(students[i].phoneNumber);
		lvItem.pszText = &phoneNumber[0]; // 插入学号
		ListView_SetItemText(hListView1, i, 4, lvItem.pszText);
	}
	for (int i = 0; i < scores.size(); i++) {
		LVITEM lvItem;
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		wstring studentID = string2wstring(scores[i].studentID);
		lvItem.pszText = &studentID[0]; // 插入姓名

		// 插入第一列的数据
		ListView_InsertItem(hListView2, &lvItem);

		lvItem.iSubItem = 1;
		std::wstring courseCode = string2wstring(scores[i].courseCode);
		lvItem.pszText = &courseCode[0]; // 插入电话
		ListView_SetItemText(hListView2, i, 1, lvItem.pszText);

		lvItem.iSubItem = 2;
		std::wstring courseName = string2wstring(scores[i].courseName);
		lvItem.pszText = &courseName[0]; // 插入学号
		ListView_SetItemText(hListView2, i, 2, lvItem.pszText);

		// 插入其他列的数据
		std::wstring credit = std::to_wstring(scores[i].credit);
		std::wstring regularScore = std::to_wstring(scores[i].regularScore);
		std::wstring labScore = std::to_wstring(scores[i].labScore);
		std::wstring examScore = std::to_wstring(scores[i].examScore);
		std::wstring compositeScore = std::to_wstring(scores[i].compositeScore);

		lvItem.iSubItem = 3;
		lvItem.pszText = (LPWSTR)credit.c_str(); // 插入数学成绩
		ListView_SetItemText(hListView2, i, 3, lvItem.pszText);

		lvItem.iSubItem = 4;
		lvItem.pszText = (LPWSTR)regularScore.c_str(); // 插入英语成绩
		ListView_SetItemText(hListView2, i, 4, lvItem.pszText);

		lvItem.iSubItem = 5;
		lvItem.pszText = (LPWSTR)labScore.c_str(); // 插入数学成绩
		ListView_SetItemText(hListView2, i, 5, lvItem.pszText);

		lvItem.iSubItem = 6;
		lvItem.pszText = (LPWSTR)examScore.c_str(); // 插入英语成绩
		ListView_SetItemText(hListView2, i, 6, lvItem.pszText);

		lvItem.iSubItem = 7;
		lvItem.pszText = (LPWSTR)compositeScore.c_str(); // 插入英语成绩
		ListView_SetItemText(hListView2, i, 7, lvItem.pszText);
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
		case IDM_LOAD:
		{
			 f1 = read_contact_file();
			 f2 = read_contact_file();
			loadData(f1, f2);
			// 将manager中的联系人信息显示到列表视图控件中
			fresh_list();
		}
		break;
		case IDM_ADD:
		{
			hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 110, 100, 20, hWnd, NULL, hInst, NULL);
			hTextBox2 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 130, 100, 20, hWnd, NULL, hInst, NULL);
			hTextBox3 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 150, 100, 20, hWnd, NULL, hInst, NULL);
			hTextBox4 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 170, 100, 20, hWnd, NULL, hInst, NULL);
			hTextBox5 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 190, 100, 20, hWnd, NULL, hInst, NULL);
			hTextBox6 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 210, 100, 20, hWnd, NULL, hInst, NULL);
			hTextBox7 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 230, 100, 20, hWnd, NULL, hInst, NULL);

			hlabel1 = CreateWindowW(L"STATIC", L"学号", WS_CHILD | WS_VISIBLE,
				920, 110, 80, 20, hWnd, NULL, hInst, NULL);
			hlabel2 = CreateWindowW(L"STATIC", L"课程号", WS_CHILD | WS_VISIBLE,
				920, 130, 80, 20, hWnd, NULL, hInst, NULL);
			hlabel3 = CreateWindowW(L"STATIC", L"课程名", WS_CHILD | WS_VISIBLE,
				920, 150, 80, 20, hWnd, NULL, hInst, NULL);
			hlabel4 = CreateWindowW(L"STATIC", L"学分", WS_CHILD | WS_VISIBLE,
				920, 170, 80, 20, hWnd, NULL, hInst, NULL);
			hlabel5 = CreateWindowW(L"STATIC", L"平时成绩", WS_CHILD | WS_VISIBLE,
				920, 190, 80, 20, hWnd, NULL, hInst, NULL);
			hlabel6 = CreateWindowW(L"STATIC", L"实验成绩", WS_CHILD | WS_VISIBLE,
				920, 210, 80, 20, hWnd, NULL, hInst, NULL);
			hlabel7 = CreateWindowW(L"STATIC", L"考试成绩", WS_CHILD | WS_VISIBLE,
				920, 230, 80, 20, hWnd, NULL, hInst, NULL);

			hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
			mode = IDM_ADD;
		}
		break;
		case IDM_MODIFY:
		{
			hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				800, 110, 50, 20, hWnd, NULL, hInst, NULL);
			hTextBox2 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				800, 130, 50, 20, hWnd, NULL, hInst, NULL);
			hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
			//manager.modifyContact();
			mode = IDM_MODIFY;
		}
		break;
		case IDM_DELETE:
		{
			hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 110, 100, 20, hWnd, NULL, hInst, NULL);

			hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
			mode = IDM_DELETE;
		}
		break;
		case IDM_EXIT:
		{
			saveData();
			DestroyWindow(hWnd);
		}
		break;
		case IDM_STUSEARCH: {
			hStuIDRadioButton = CreateWindowEx(
				0,
				L"BUTTON",
				L"ID",
				WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
				1000, 240, 100, 30,
				hWnd,
				NULL, // 修改为不同的标识符
				hInst,
				NULL);

			hStuNameRadioButton = CreateWindowEx(
				0,
				L"BUTTON",
				L"姓名",
				WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
				1000, 270, 100, 30,
				hWnd,
				NULL, // 修改为不同的标识符
				hInst,
				NULL);
			hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 110, 100, 20, hWnd, NULL, hInst, NULL);

			hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
			mode = IDM_STUSEARCH;
		}break;
		case IDM_SCOSEARCH: {
			hTextBox1 = CreateWindowW(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,
				1000, 110, 100, 20, hWnd, NULL, hInst, NULL);

			hButton1 = CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
			mode = IDM_SCOSEARCH;

		}break;
		case IDM_SORT: {
			hStuIDRadioButton = CreateWindowEx(
				0,
				L"BUTTON",
				L"综合成绩升序",
				WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
				1000, 240, 200, 30,
				hWnd,
				NULL, // 修改为不同的标识符
				hInst,
				NULL);

			hStuNameRadioButton = CreateWindowEx(
				0,
				L"BUTTON",
				L"实得学分升序",
				WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
				1000, 270, 200, 30,
				hWnd,
				NULL, // 修改为不同的标识符
				hInst,
				NULL);
			hButton1= CreateWindow(TEXT("button"), TEXT("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								800, 300, 100, 30, hWnd, (HMENU)IDM_CONFIRM, hInst, NULL);
			mode = IDM_SORT;
		}break;
		case IDM_CONFIRM:
		{
			switch (mode)
			{
			case IDM_ADD:
			{
				string stuID, courseID, courseName, credit, usualGrade, experimentGrade, examGrade;
				// 获取第一个输入框的文本
				int textLength = GetWindowTextLengthW(hTextBox1);
				wchar_t* buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox1, buffer, textLength + 1);
				stuID = wstring2string(buffer);
				delete[] buffer;

				// 获取第二个输入框的文本
				textLength = GetWindowTextLengthW(hTextBox2);
				buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox2, buffer, textLength + 1);
				courseID = wstring2string(buffer);
				delete[] buffer;

				// 获取第三个输入框的文本
				textLength = GetWindowTextLengthW(hTextBox3);
				buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox3, buffer, textLength + 1);
				courseName = wstring2string(buffer);
				delete[] buffer;

				textLength = GetWindowTextLengthW(hTextBox4);
				buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox4, buffer, textLength + 1);
				credit = wstring2string(buffer);
				delete[] buffer;

				textLength = GetWindowTextLengthW(hTextBox5);
				buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox5, buffer, textLength + 1);
				usualGrade = wstring2string(buffer);
				delete[] buffer;

				textLength = GetWindowTextLengthW(hTextBox6);
				buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox6, buffer, textLength + 1);
				experimentGrade = wstring2string(buffer);
				delete[] buffer;

				textLength = GetWindowTextLengthW(hTextBox7);
				buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox7, buffer, textLength + 1);
				examGrade = wstring2string(buffer);
				delete[] buffer;

				inputData(stuID, courseID, courseName, stoi(credit), stoi(usualGrade), stoi(experimentGrade), stoi(examGrade));
			}
			break;
			case IDM_DELETE:
			{
				int textLength = GetWindowTextLengthW(hTextBox1);
				wchar_t* buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox1, buffer, textLength + 1);
				string stuID = wstring2string(buffer);
				delete[] buffer;
				deleteStudent(stuID);
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
				//manager.modifyContact(name, phoneNumber);
			}break;
			case IDM_STUSEARCH:
			{
				int StuIDCheckState = SendMessage(hStuIDRadioButton, BM_GETCHECK, 0, 0);
				int StuNameCheckState = SendMessage(hStuNameRadioButton, BM_GETCHECK, 0, 0);				
				int choice = 0;
				int textLength = GetWindowTextLengthW(hTextBox1);
				wchar_t* buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox1, buffer, textLength + 1);
				string stuID, stuName;
				if (StuIDCheckState == BST_CHECKED)
				{
					choice = 1;
					 stuID = wstring2string(buffer);
				}
				else if (StuNameCheckState == BST_CHECKED)
				{
					choice = 2;
					 stuName = wstring2string(buffer);
				}
				delete[] buffer;
				wstring messageText = string2wstring(searchStudentInfo(choice, stuID, stuName));
				//用messagebox显示searchStudentInfo的信息
				MessageBoxW(hWnd, messageText.c_str(), L"", MB_OK);
			}
			break;
			case IDM_SCOSEARCH: {
				int textLength = GetWindowTextLengthW(hTextBox1);
				wchar_t* buffer = new wchar_t[textLength + 1];
				GetWindowTextW(hTextBox1, buffer, textLength + 1);
				string stuID = wstring2string(buffer);
				delete[] buffer;
				wstring messageText = string2wstring(searchScoreInfo(stuID));
				//用messagebox显示searchStudentInfo的信息
				MessageBoxW(hWnd, messageText.c_str(), L"", MB_OK);
			}break;
			case IDM_SORT: {
				int StuIDCheckState = SendMessage(hStuIDRadioButton, BM_GETCHECK, 0, 0);
				int StuNameCheckState = SendMessage(hStuNameRadioButton, BM_GETCHECK, 0, 0);
				int choice = 0;
				if (StuIDCheckState == BST_CHECKED)
				{
					choice = 1;
				}
				else if (StuNameCheckState == BST_CHECKED)
				{
					choice = 2;
				}
				sortScores(choice);

			}break;
			}
			DestroyWindow(hTextBox1);
			DestroyWindow(hTextBox2);
			DestroyWindow(hTextBox3);
			DestroyWindow(hTextBox4);
			DestroyWindow(hTextBox5);
			DestroyWindow(hTextBox6);
			DestroyWindow(hTextBox7);
			DestroyWindow(hlabel1);
			DestroyWindow(hlabel2);
			DestroyWindow(hlabel3);
			DestroyWindow(hlabel4);
			DestroyWindow(hlabel5);
			DestroyWindow(hlabel6);
			DestroyWindow(hlabel7);
			DestroyWindow(hStuNameRadioButton);
			DestroyWindow(hStuIDRadioButton);
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
