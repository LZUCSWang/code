#pragma once
#define MAX_LOADSTRING 100

#define ID_CHINESE_RADIOBUTTON 101
#define ID_MATH_RADIOBUTTON 102
#define ID_ENGLISH_RADIOBUTTON 103
#define ID_ASCENDING_RADIOBUTTON 104
#define ID_DESCENDING_RADIOBUTTON 105

#include <Commdlg.h>
#include "resource.h"
// ȫ�ֱ���:
HINSTANCE hInst;                     // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];       // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING]; // ����������

// ҳ�����Ͱ�ť���
HWND hMainPage;
HWND hSecondPage1, hSecondPage2, hSecondPage3, hSecondPage4, hSecondPage5, hSecondPage6, hSecondPage7, hSecondPage8, hSecondPage9;
HWND hCurrentPage;
HWND hReturnButton;
HWND hButton1, hButton2, hButton3, hButton4, hButton5, hButton6, hButton7, hButton8, hButton9;
HWND hTextBoxa1, hTextBoxa2, hTextBoxa3, hTextBoxa4, hTextBoxa5;
HWND hTextBoxb1, hTextBoxb2, hTextBoxb3, hTextBoxb4, hTextBoxb5;
HWND hSubmitButton, hSubmitButton1, hSubmitButton2;
HWND hListView;
HWND hChineseRadioButton, hMathRadioButton, hEnglishRadioButton, hAscendingRadioButton, hDescendingRadioButton, hChineseRadioButton1, hMathRadioButton1, hEnglishRadioButton1;
const int COLUMN_COUNT = 5;
const wchar_t* columnHeaders[COLUMN_COUNT] = { L"Name", L"ID", L"Chinese", L"Math", L"English" };
