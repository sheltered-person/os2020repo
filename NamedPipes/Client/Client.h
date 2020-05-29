#pragma once
#include <iostream>
#include <string>

#include "ClientPipe.h"
#include "../Server/SimplePipe.h"
#include "EmployeeData.h"

class Client
{
private:
	static const std::string PIPE_NAME_PREFIX;
	ClientPipe *pipe;

public:
	static Client& Create();

	bool ConnectServer();
	bool DisconnectServer();

	Employee ReadEmployee(int employeeNum, bool isReadOnly);
	void WriteEmployee(Employee employee);

	void SendReleaseMessage(int employeeNum);
	void SendEndMessage();

	virtual ~Client();
};