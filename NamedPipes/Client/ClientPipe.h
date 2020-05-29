#pragma once
#include <iostream>
#include <Windows.h>

#include "../Server/SimplePipe.h"
#include "../Server/ServerNames.h"


class ClientPipe
{
private:
	HANDLE hPipe;
	std::string name;

public:
	ClientPipe(std::string name);

	std::string GetName() const;

	bool ConnectServer();
	bool DisconnectServer();

	void SendNewMessage(Message message);
	void ReceiveMessage(Message& message);

	virtual ~ClientPipe();
};
