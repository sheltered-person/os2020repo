#include "Server.h"

Server & Server::Create()
{
	return *(new Server());
}

void Server::OpenFile(std::string fileName, int recordsCount)
{
	binary = new File(fileName, recordsCount);
}

void Server::ModifyRecord(int employeeNum, State toChange)
{
	csRecords.EnterSection();

	if (records.find(employeeNum) == records.end())
	{
		csRecords.LeaveSection();
		return;
	}
	else
	{
		Record* record = &records[employeeNum];
		const int sleepInterval = 1;

		switch (toChange)
		{
		case State::None:
			record->threadsCount--;

			if (record->threadsCount == 0)
				record->state = State::None;

			break;

		case State::Write:
			while (record->state != State::None)
			{
				csRecords.LeaveSection();
				Sleep(sleepInterval);
				csRecords.EnterSection();
			}

			record->state = State::Write;
			record->threadsCount++;

			break;

		case State::Read:
			while (record->state == State::Write)
			{
				csRecords.LeaveSection();
				Sleep(sleepInterval);
				csRecords.EnterSection();
			}

			record->state = State::Read;
			record->threadsCount++;

			break;
		}

		csRecords.LeaveSection();
	}
}

void Server::AddEmployee(Employee employee)
{
	int offset = binary->GetPointer();

	records[employee.num].offset = offset;
	binary->WriteBuffer(&employee, sizeof(Employee), offset);
}

Employee Server::ReadEmployee(int employeeNum)
{
	csRecords.EnterSection();

	if (records.find(employeeNum) == records.end() || 
		records[employeeNum].state != State::Read)
	{
		csRecords.LeaveSection();
		return Employee();
	}

	int offset = records[employeeNum].offset;
	csRecords.LeaveSection();

	Employee employee;
	binary->ReadBuffer(&employee, sizeof(Employee), offset);

	return employee;
}

void Server::WriteEmployee(Employee employee)
{
	csRecords.EnterSection();

	if (records.find(employee.num) == records.end() || 
		records[employee.num].state != State::Write)
	{
		csRecords.LeaveSection();
		return;
	}

	int offset = records[employee.num].offset;
	csRecords.LeaveSection();

	binary->WriteBuffer(&employee, sizeof(Employee), offset);
}

void Server::PrintData(std::ostream & out) const
{
	for (auto record : records)
	{
		Employee next = { 0, "", 0 };
		binary->ReadBuffer(&next, sizeof(Employee), record.second.offset);
		out << next.num << "\t" << next.name << "\t" << next.hours << "\n";
	}
}

Server::~Server()
{
	delete binary;
}
