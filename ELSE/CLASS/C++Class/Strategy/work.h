#pragma once
using namespace std;
#include <bits/stdc++.h>
class Worker // ְ��������
{
public:
    virtual void showInfo() = 0;      // ��ʾ������Ϣ
    virtual string getDeptName() = 0; // ��ȡ��λ����
    int m_Id;                         // ְ�����
    string m_Name;                    // ְ������
    int m_DeptId;                     // ���ű��
};
class Manager : public Worker
{
public:
    Manager(int id, string name, int dId) // ���캯��
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = dId;
    }
    void showInfo() // ��ʾ������Ϣ
    {
        cout << "ְ�����: " << this->m_Id
             << "\tְ������: " << this->m_Name
             << "\t��λ: " << this->getDeptName()
             << "\t��λְ��: ����ϰ彻�������񣬲��·������Ա��" << endl;
    }

private:
    string getDeptName() // ��ȡ��λ����
    {
        return string("����");
    }
};
class Employee : public Worker // ��ͨԱ����
{
public:
    Employee(int id, string name, int dId)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = dId;
    }
    void showInfo()
    {
        cout << "ְ�����: " << this->m_Id
             << "\tְ������: " << this->m_Name
             << "\t��λ: " << this->getDeptName()
             << "\t��λְ��: ��ɾ�����������" << endl;
    }

private:
    string getDeptName()
    {
        return string("Ա��");
    }
};
class Boss : public Worker // �ϰ���
{
public:
    Boss(int id, string name, int dId)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = dId;
    }
    void showInfo()
    {
        cout << "ְ�����: " << this->m_Id
             << "\tְ������: " << this->m_Name
             << "\t��λ: " << this->getDeptName()
             << "\t��λְ��: ����˾��������" << endl;
    }

private:
    string getDeptName()
    {
        return string("�ܲ�");
    }
};
class allWorker
{
public:
    void addWorker(std::unique_ptr<Worker> s) // ���ְ��
    {
        workerList.push_back(move(s));
    }
    void showAllWorker() // ��ʾ����ְ��
    {
        for (auto &i : workerList)
        {
            i->showInfo();
        }
    }

private:
    vector<std::unique_ptr<Worker>> workerList; // ְ���б�
};