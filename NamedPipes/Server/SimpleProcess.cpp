#include "SimpleProcess.h"


int SimpleProcess::leavedIDRequest = -1;


DWORD _stdcall ThreadFuncCall(LPVOID params)
{
	SimplePipe* pipe = (SimplePipe*)params;

	if (pipe == nullptr || !pipe->ConnectClient())
		return 1;

	Server server = Server::Create();

	Message in;
	in.type = Type::End;

	Message out;
	out.type = Type::Success;
	out.buffer = nullptr;

	pipe->ReceiveMessage(in);
	SimpleProcess::leavedIDRequest = -1;

	while (in.type != Type::End)
	{
		Employee employee;
		int employeeNum;

		switch (in.type)
		{
		case Type::Read:
			bool isReadOnly;

			memcpy(&employeeNum, in.buffer, sizeof(int));
			memcpy(&isReadOnly, in.buffer + sizeof(int), sizeof(bool));
			SimpleProcess::leavedIDRequest = employeeNum;

			State newState;

			if (isReadOnly)
				newState = State::Read;
			else
				newState = State::Write;

			server.ModifyRecord(employeeNum, newState);
			employee = server.ReadEmployee(employeeNum);

			memcpy(out.buffer, &employee, sizeof(employee));
			out.type = Type::Send;

			break;

		case Type::Write:
			memcpy(&employee, in.buffer, sizeof(employee));
			SimpleProcess::leavedIDRequest = employee.num;

			server.WriteEmployee(employee);
			out.type = Type::Success;

			break;

		case Type::Release:
			memcpy(&employeeNum, in.buffer, sizeof(int));
			SimpleProcess::leavedIDRequest = employee.num;

			server.ModifyRecord(employeeNum, State::None);
			out.type = Type::Success;
			SimpleProcess::leavedIDRequest = -1;

			break;
		}

		if (in.type != Type::End)
		{
			pipe->SendNewMessage(out);
			pipe->ReceiveMessage(in);
		}
	}

	return 0;
}

SimpleProcess::SimpleProcess(const std::string path, const std::string commandLine)
{
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	BOOL isCreated = CreateProcess(
		path.c_str(),
		nullptr,
		nullptr,
		nullptr,
		FALSE,
		CREATE_NEW_CONSOLE | CREATE_SUSPENDED,
		nullptr,
		nullptr,
		&si,
		&pi
	);

	hThread = CreateThread(
		NULL,
		0,
		ThreadFuncCall,
		(LPVOID)pipe,
		CREATE_SUSPENDED,
		NULL
	);

	pipe = new SimplePipe(pipeName + std::to_string(pi.dwProcessId));
}

int SimpleProcess::GetProcessID() const
{
	return pi.dwProcessId;
}

void SimpleProcess::WaitThread()
{
	WaitForSingleObject(
		hThread, 
		INFINITE
	);
}

void SimpleProcess::RunThread()
{
	ResumeThread(hThread);
	ResumeThread(pi.hThread);
}


SimpleProcess::~SimpleProcess()
{
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	CloseHandle(hThread);

	delete pipe;
}