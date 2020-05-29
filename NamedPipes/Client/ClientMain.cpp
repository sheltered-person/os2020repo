#include <iostream>
#include <string>

#include "Client.h"
#include "../Server/ServerNames.h"
#include "EmployeeData.h"


int main()
{
	std::cout << "Client process are connecting.\n";

	Client client = Client::Create();
	client.ConnectServer();

	std::cout << "Sucessfully connected.\n";

	int key = 1;
	
	while (key != 0)
	{
		std::cout << "Choose action:" 
			<< "\n\t1. Read employee data." 
			<< "\n\t2. Update employee data."
			<< "\n\t0. Exit this process.\n";

		std::cin >> key;

		Employee employee;
		int employeeNum = 0;

		switch (key)
		{
		case 1:
			std::cout << "Enter employee ID: ";
			std::cin >> employeeNum;

			std::cout << "Waiting for server response.\n";
			employee = client.ReadEmployee(employeeNum, true);

			employeeNum = employee.num;

			if (employeeNum < 0)
				std::cout << "Invalid employee ID number.\n";
			else
			{
				std::cout << "ID\tName\tHours";
				std::cout << employee.num << "\t" << employee.name << "\t" << employee.hours << "\n";
			}

			break;

		case 2:
			std::cout << "Enter employee ID: ";
			std::cin >> employeeNum;

			std::cout << "Waiting for server response.\n";
			client.ReadEmployee(employeeNum, false);

			employeeNum = employee.num;

			if (employeeNum < 0)
				std::cout << "Invalid employee ID number.\n";
			else
			{
				std::cout << "ID\tName\tHours";
				std::cout << employee.num << "\t" << employee.name << "\t" << employee.hours << "\n";

				employee = ReadEmployeeFromStdin();

				std::cout << "Waiting for server response.\n";
				client.WriteEmployee(employee);
			}

			break;

		default:
			if (employeeNum >= 0)
				client.SendReleaseMessage(employeeNum);
		}
	}

	return 0;
}