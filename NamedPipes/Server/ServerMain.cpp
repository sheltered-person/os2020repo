#include <iostream>
#include <vector>

#include "Server.h"
#include "SimpleProcess.h"
#include "ServerNames.h"
#include "EmployeeData.h"


int main()
{
	std::string fileName;
	std::cout << "Enter binary file name: ";
	std::cin >> fileName;

	int recordsCount = 0;
	std::cout << "Enter the amount of records: ";
	std::cin >> recordsCount;

	std::vector<Employee> employes = ReadEmployes(recordsCount);

	Server server = Server::Create();
	server.OpenFile(fileName, recordsCount);

	for (auto employee : employes)
		server.AddEmployee(employee);

	system("cls");

	std::cout << "ID\tName\tHours\n\n";
	server.PrintData(std::cout);

	int clientsCount = 0;
	std::cout << "Enter clients amount: ";
	std::cin >> clientsCount;

	SimpleProcess** processes = new SimpleProcess*[clientsCount];

	for (int i = 0; i < clientsCount; i++)
	{
		processes[i] = new SimpleProcess(clientPath, "");
		processes[i]->RunThread();
	}

	for (int i = 0; i < clientsCount; i++)
		processes[i]->WaitThread();

	std::cout << "Modified file " << fileName << ":\n";
	server.PrintData(std::cout);

	system("pause");
	return 0;
}