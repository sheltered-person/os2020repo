#include <iostream>
#include "EmployeeData.h"


Employee ReadEmployeeFromStdin()
{
	Employee employee;

	std::cout << "\tEnter id number: ";
	std::cin >> employee.num;

	std::cout << "\tEnter name: ";
	std::cin >> employee.name;

	std::cout << "\tEnter number of hours: ";
	std::cin >> employee.hours;

	return employee;
}

std::vector<Employee> ReadEmployes(int recordsCount)
{
	std::vector<Employee> employes(recordsCount);

	for (Employee& employee : employes)
	{
		std::cout << "Enter next employee data:\n";
		employee = ReadEmployeeFromStdin();
	}

	return employes;
}
