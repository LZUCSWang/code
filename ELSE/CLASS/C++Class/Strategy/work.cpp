#include "work.h"
int main()
{
    allWorker worker;
    worker.addWorker(make_unique<Employee>(1, "����", 1));
    worker.addWorker(make_unique<Employee>(2, "����", 1));
    worker.addWorker(make_unique<Employee>(3, "����", 1));
    worker.addWorker(make_unique<Manager>(4, "����", 2));
    worker.addWorker(make_unique<Boss>(5, "����", 3));
    
    worker.showAllWorker();
}