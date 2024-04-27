#pragma once
using namespace std;
#include <bits/stdc++.h>
class Worker // 职工抽象类
{
public:
    virtual void showInfo() = 0;      // 显示个人信息
    virtual string getDeptName() = 0; // 获取岗位名称
    int m_Id;                         // 职工编号
    string m_Name;                    // 职工姓名
    int m_DeptId;                     // 部门编号
};
class Manager : public Worker
{
public:
    Manager(int id, string name, int dId) // 构造函数
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = dId;
    }
    void showInfo() // 显示个人信息
    {
        cout << "职工编号: " << this->m_Id
             << "\t职工姓名: " << this->m_Name
             << "\t岗位: " << this->getDeptName()
             << "\t岗位职责: 完成老板交给的任务，并下发任务给员工" << endl;
    }

private:
    string getDeptName() // 获取岗位名称
    {
        return string("经理");
    }
};
class Employee : public Worker // 普通员工类
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
        cout << "职工编号: " << this->m_Id
             << "\t职工姓名: " << this->m_Name
             << "\t岗位: " << this->getDeptName()
             << "\t岗位职责: 完成经理交给的任务" << endl;
    }

private:
    string getDeptName()
    {
        return string("员工");
    }
};
class Boss : public Worker // 老板类
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
        cout << "职工编号: " << this->m_Id
             << "\t职工姓名: " << this->m_Name
             << "\t岗位: " << this->getDeptName()
             << "\t岗位职责: 管理公司所有事务" << endl;
    }

private:
    string getDeptName()
    {
        return string("总裁");
    }
};
class allWorker
{
public:
    void addWorker(std::unique_ptr<Worker> s) // 添加职工
    {
        workerList.push_back(move(s));
    }
    void showAllWorker() // 显示所有职工
    {
        for (auto &i : workerList)
        {
            i->showInfo();
        }
    }

private:
    vector<std::unique_ptr<Worker>> workerList; // 职工列表
};