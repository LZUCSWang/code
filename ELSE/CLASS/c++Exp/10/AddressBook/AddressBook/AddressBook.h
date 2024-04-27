#pragma once

#include <CommCtrl.h>
#include <iostream>
#include <string>
// ��ͷ�ļ��а���Windows API
#include <Windows.h>
#include <bits/stdc++.h>
#include "resource.h"
#include <Commdlg.h>
#define IDM_VIEW 1
#define IDM_ADD 2
#define IDM_DIAL 3
#define IDM_MODIFY 4
#define IDM_DELETE 5
#define IDM_SAVE 7
#define IDM_READ 8
#define IDM_CHANGE 9
#define IDM_FIND 10
#define MAX_LOADSTRING 100
#define IDM_CONFIRM 11
HWND hWnd;
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
const int COLUMN_COUNT = 4;
const wchar_t* columnHeaders[COLUMN_COUNT] = { L"����", L"����", L"���", L"����"};
HWND hListView;
struct Contact
{
	std::string name, phoneNumber, category,email;
	Contact* next;
};
HWND hOfficialRadioButton, hIndividualRadioButton, hBusinessRadioButton;
HWND hTextBox1, hTextBox2, hTextBox3, hTextBox4, hButton1;
HWND hlabel1, hlabel2, hlabel3, hlabel4;
int mode = 0;
//HWND hCurrentPage;
//HWND hSecondPage;