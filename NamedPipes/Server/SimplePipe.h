#pragma once
#include <Windows.h>
#include <iostream>

#include "ServerNames.h"


enum class Type
{
	Read,
	Write,
	Send,
	Release,
	Success,
	End
};


typedef struct Message
{
	Type type;
	int* buffer;
} Message;


class SimplePipe
{
private:
	HANDLE hPipe;

	OVERLAPPED overlapped;
	const char* name;

	int timeout = 5000U;

public:
	SimplePipe(std::string pipeName);
	std::string GetName() const;

	bool ConnectClient();
	bool DisconnectClient();

	void SendNewMessage(Message message);
	void ReceiveMessage(Message& message);

	virtual ~SimplePipe();
};

