#include "ClientPipe.h"

ClientPipe::ClientPipe(std::string name)
{
	this->name = name;
}

std::string ClientPipe::GetName() const
{
	return name;
}

bool ClientPipe::ConnectServer()
{
	hPipe = CreateFile(
		name.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		nullptr,
		OPEN_EXISTING,
		0,
		nullptr
	);

	if (hPipe == INVALID_HANDLE_VALUE)
		return false;

	DWORD dwReadmode = PIPE_READMODE_MESSAGE;

	BOOL isHandleStateSet = SetNamedPipeHandleState(
		hPipe,
		&dwReadmode,
		nullptr,
		nullptr
	);

	return isHandleStateSet;
}

bool ClientPipe::DisconnectServer()
{
	BOOL result = CloseHandle(hPipe);

	if (result)
		hPipe = nullptr;

	return result;
}

void ClientPipe::SendNewMessage(Message message)
{
	DWORD dwSent;

	WriteFile(
		hPipe, 
		&message, 
		sizeof(Message), 
		&dwSent, 
		nullptr
	);
}

void ClientPipe::ReceiveMessage(Message & message)
{
	DWORD dwSent;

	ReadFile(
		hPipe, 
		&message, 
		sizeof(Message), 
		&dwSent, 
		nullptr
	);
}

ClientPipe::~ClientPipe()
{
	DisconnectServer();
}
