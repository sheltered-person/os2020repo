#include "SalaryCounter.h"


double SalaryCounter::CountSalary(const Employee& employee, int salary)
{
    return (double)employee.hours * salary;
}