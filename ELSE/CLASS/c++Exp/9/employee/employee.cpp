#include "employee.h"
using namespace std;
employee::employee(int id, const string &name, char gender, const Date &birth, const string &position, double salary) : id_(id), name_(name), gender_(gender), birth_(birth), position_(position), salary_(salary) {}

void DisplayEmployee(const employee &e, ostream &fout)
{
    fout << "==============================" << endl;
    fout << "ID:" << e.id_ << endl;
    fout << "Name:" << e.name_ << endl;
    fout << "Gender:" << e.gender_ << endl;
    fout << "Birthday:" << e.birth_.GetYear() << "." << e.birth_.GetMonth() << "." << e.birth_.GetDay() << endl;
    fout << "Position:" << e.position_ << endl;
    fout << "Salary:" << e.salary_ << endl;
}
