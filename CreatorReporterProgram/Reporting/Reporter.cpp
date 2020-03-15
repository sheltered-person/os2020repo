#include "Reporter.h"


Reporter::Reporter(string binarySource, string reportFileName, int salaryForHour)
{
    this->binarySource = binarySource;
    this->reportFileName = reportFileName;
    this->salaryForHour = salaryForHour;
}


void Reporter::Run()
{
    ifstream in(binarySource, ios::binary);

    if (!in.is_open())
        return;

    ofstream out(reportFileName);

    out << "Report from file \"" << reportFileName << "\" \n\n";

    int entriesAmount;
    in >> entriesAmount;

    out << "Number\tName\tHours\tSalary\n";

    for (int i = 0; i < entriesAmount; i++)
    {
        Employee employee;
        in >> employee.num >> employee.name >> employee.hours;

        out << employee.num << "\t" << employee.name << "\t" << employee.hours << "\t"
             << SalaryCounter::CountSalary(employee, salaryForHour) << "\n";
    }

    cout << "Text report from binary file is created.\n\n";
}


Reporter::~Reporter() { }
