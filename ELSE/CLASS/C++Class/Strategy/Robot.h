#pragma once
#include <iostream>
#include <memory>

class IStrategy // 抽象基类
{
public:
    virtual ~IStrategy() {}         // 析构函数
    virtual void moveCommand() = 0; // 纯虚函数
};

class AggressiveStrategy : public IStrategy // 继承虚基类，实现进攻策略
{
public:
    void moveCommand() // 实现接口
    {
        std::cout << "Aggressive Strategy: attack any robot when found"
                  << "\n";
    }
};
class NeutralStrategy : public IStrategy // 继承父类，实现中立策略
{
public:
    void moveCommand()
    {
        std::cout << "Neutral Strategy: attack only when attacked, else ignore"
                  << "\n";
    }
};
class DefensiveStrategy : public IStrategy // 继承父类，实现防御策略
{
public:
    void moveCommand()
    {
        std::cout << "Defensive Strategy: avoid confrontation at all cost, run when possible"
                  << "\n";
    }
};
class Robot
{
public:
    Robot(std::string name) :             // 构造函数
                              _name(name) // 初始化列表,初始化_name
    {
    }
    void setStrategy(std::unique_ptr<IStrategy> s)
    {
        _strategy = std::move(s); // 将传入策略的对象的状态或者所有权转移到Robot的私有成员_strategy中进行策略的设置，只是转移，没有内存的搬迁或者内存拷贝。
    }
    void executeCommand()
    {
        _strategy->moveCommand(); // 执行策略
    }

private:
    std::unique_ptr<IStrategy> _strategy; // 策略指针
    std::string _name;                    // Robot 名字
};