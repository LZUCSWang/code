/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Salesmanager.h
 * @Description: 销售经理类头文件
 */

#ifndef SALESMANAGER_H
#define SALESMANAGER_H

#include "Manager.h"
#include "Salesman.h"

// Salesmanager 类
class Salesmanager : public Manager, public Salesman
{
public:
    Salesmanager() {} // 默认构造函数
    Salesmanager(int id, const string &name, char gender, const Date &birth, const string &department); // 带参数构造函数
    double pay() const override; // 计算工资的函数
    void display() const override; // 显示销售经理信息的函数
    void promote(double salary) const override; // 职位晋升函数
};

#endif
