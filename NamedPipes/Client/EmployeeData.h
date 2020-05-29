#pragma once
#include <vector>
#include <fstream>
#include <map>


typedef struct Employee 
{
	int num;
	char name[10];
	double hours;
} Employee;


enum class State
{
	None = 0,
	Read = 1,
	Write = 2
};


typedef struct Record
{
	State state;
	int threadsCount;
	int offset;
} Record;


Employee ReadEmployeeFromStdin();

std::vector<Employee> ReadEmployes(int recordsCount);

void PrintEmployes(std::string fileName, int recordsCount);
