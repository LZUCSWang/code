#include "work.h"
int main()
{
    allWorker worker;
    worker.addWorker(make_unique<Employee>(1, "张三", 1));
    worker.addWorker(make_unique<Employee>(2, "李四", 1));
    worker.addWorker(make_unique<Employee>(3, "王五", 1));
    worker.addWorker(make_unique<Manager>(4, "赵六", 2));
    worker.addWorker(make_unique<Boss>(5, "孙七", 3));
    
    worker.showAllWorker();
}