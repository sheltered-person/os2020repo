#pragma once
#include <iostream>
#include <map>

#include "EmployeeData.h"
#include "CriticalSection.h"
#include "File.h"


class Server
{
private:
	std::map<int, Record> records;
	File* binary;

	CriticalSection csRecords;

public:
	static Server& Create();

	void OpenFile(std::string fileName, int recordsCount);
	void ModifyRecord(int employeeNum, State toChange);

	void AddEmployee(Employee employee);
	Employee ReadEmployee(int employeeNum);
	void WriteEmployee(Employee employee);

	void PrintData(std::ostream& out) const;

	virtual ~Server();
};

