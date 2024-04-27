#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long
//抽象cpu
class CPU
{
public:
    virtual void cal() = 0;
};
//抽象显卡类
class Xian
{
public:
    virtual void display() = 0;
};
//抽象内存类
class Mem
{
public:
    virtual void storage() = 0;
};

class Computer
{
public:
    Computer(CPU *cpu, Xian *xian, Mem *mem)
    {
        m_cpu = cpu;
        m_xian = xian;
        m_mem = mem;
    }
    void work()
    {
        m_cpu->cal();
        m_xian->display();
        m_mem->storage();
    }

private:
    CPU *m_cpu;
    Xian *m_xian;
    Mem *m_mem;
};

// Intel
class IntelCPU : public CPU
{
public:
    virtual void cal()
    {
        cout << "Inter CPU" << endl;
    }
};
class IntelXian : public Xian
{
public:
    virtual void display()
    {
        cout << "Intel Xian" << endl;
    }
};

class IntelMem : public Mem
{
public:
    virtual void storage()
    {
        cout << "Intel Mem" << endl;
    }
};
class AMDCPU : public CPU
{
public:
    virtual void cal()
    {
        cout << "Inter CPU" << endl;
    }
};
class AMDXian : public Xian
{
public:
    virtual void display()
    {
        cout << "Intel Xian" << endl;
    }
};

class AMDMem : public Mem
{
public:
    virtual void storage()
    {
        cout << "Intel Mem" << endl;
    }
};

void test1()
{
    CPU *intelCPU = new IntelCPU;
    Xian *intelxian = new IntelXian;
    Mem *intelMem = new IntelMem;
    Computer *computer1 = new Computer(intelCPU, intelxian, intelMem);
    computer1->work();
    delete computer1;
}
int main() { test1(); }