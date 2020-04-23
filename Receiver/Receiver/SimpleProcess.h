#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <exception>


class SimpleProcess
{
private:
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

public:
	SimpleProcess(const std::string path, const std::string commandLine);

	int GetProcessID() const;

	virtual ~SimpleProcess();
};
