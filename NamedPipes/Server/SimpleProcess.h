#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <exception>

#include "SimplePipe.h"
#include "ServerNames.h"
#include "Server.h"


class SimpleProcess
{
private:
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	HANDLE hThread;
	SimplePipe* pipe;

public:
	static int leavedIDRequest;

	SimpleProcess(const std::string path, const std::string commandLine);

	int GetProcessID() const;
	void RunThread();
	void WaitThread();

	virtual ~SimpleProcess();
};
