#pragma once

#include <CommCtrl.h>
#include <iostream>
#include <string>
// ��ͷ�ļ��а���Windows API
#include <Windows.h>
#include <bits/stdc++.h>
#include "resource.h"
#include <Commdlg.h>
using namespace std;
#define IDM_STUSEARCH 1
#define IDM_ADD 2
#define IDM_EXIT 3
#define IDM_MODIFY 4
#define IDM_DELETE 5
#define IDM_SAVE 7
#define IDM_SORT 8
#define IDM_CHANGE 9
#define IDM_SCOSEARCH 10
#define IDM_LOAD 12
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
const int COLUMN_COUNT1 = 5;
const int COLUMN_COUNT2 = 8;
const wchar_t* columnHeaders1[COLUMN_COUNT1] = { L"ѧ��", L"����", L"�Ա�", L"�������" ,L"�绰����" };
const wchar_t* columnHeaders2[COLUMN_COUNT2] = { L"ѧ��", L"�γ̱��", L"�γ�����", L"ѧ��",L"ƽʱ�ɼ�",L"ʵ��ɼ�",L"����ɼ�",L"�ۺϳɼ�" };
HWND hListView1, hListView2;

string f1, f2;
// ѧ��������Ϣ�ṹ��
struct StudentInfo {
	std::string studentID;
	std::string name;
	std::string gender;
	std::string dormitory;
	std::string phoneNumber;
};

// ѧ���ɼ��ṹ��
struct StudentScore {
	std::string studentID;
	std::string courseCode;
	std::string courseName;
	int credit;
	int regularScore;
	int labScore;
	int examScore;
	double compositeScore;
};

// ��������
void loadData(string f1, string f2);
void saveData();
void inputData(string studentID, string courseCode, string courseName, int credit, int regularScore, int labScore, int examScore);
string printStudentInfo(const StudentInfo& student);
string printScoreInfo(const StudentScore& score);
string searchStudentInfo(int choice, string StuID, string StuName);
string searchScoreInfo(string stuID);
void deleteStudent(string studentID);
bool compareByCompositeScore(const StudentScore& score1, const StudentScore& score2);
bool compareByCredit(const StudentScore& score1, const StudentScore& score2);
void sortScores(int choice);
vector<StudentInfo> students;
vector<StudentScore> scores;

HWND hStuIDRadioButton, hStuNameRadioButton, hBusinessRadioButton;
HWND hTextBox1, hTextBox2, hTextBox3, hTextBox4, hTextBox5, hTextBox6, hTextBox7, hButton1;
HWND hlabel1, hlabel2, hlabel3, hlabel4, hlabel5, hlabel6, hlabel7;
int mode = 0;