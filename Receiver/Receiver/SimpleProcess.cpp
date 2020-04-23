#include "SimpleProcess.h"


SimpleProcess::SimpleProcess(const std::string path, const std::string commandLine)
{
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	BOOL isCreated = CreateProcess(
		path.c_str(),
		LPSTR(commandLine.c_str()),
		nullptr,
		nullptr,
		FALSE,
		CREATE_NEW_CONSOLE | CREATE_SUSPENDED,
		nullptr,
		nullptr,
		&si,
		&pi
	);

	if (!isCreated)
		throw "Error: process creation failed (error " +
		std::to_string(GetLastError()) + ").";

	ResumeThread(pi.hThread);
}

int SimpleProcess::GetProcessID() const
{
	return pi.dwProcessId;
}


SimpleProcess::~SimpleProcess()
{
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}