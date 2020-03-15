#ifndef CREATORREPORTERPROGRAM_SALARYCOUNTER_H
#define CREATORREPORTERPROGRAM_SALARYCOUNTER_H

#include <iostream>
#include <string>

#include "../Include/Employee.h"

using namespace std;


class SalaryCounter
{
public:
    static double CountSalary(const Employee&, int);
};


#endif //CREATORREPORTERPROGRAM_SALARYCOUNTER_H
