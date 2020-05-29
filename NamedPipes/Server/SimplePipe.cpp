#include "SimplePipe.h"

SimplePipe::SimplePipe(std::string name) : name(name.c_str())
{
	ZeroMemory(&overlapped, sizeof(OVERLAPPED));

	hPipe = CreateNamedPipe(
		(LPSTR)name.c_str(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		1,
		sizeof(Message),
		sizeof(Message),
		timeout,
		nullptr
	);

	overlapped.hEvent = CreateEvent(
		nullptr,
		TRUE,
		FALSE,
		nullptr
	);
}

std::string SimplePipe::GetName() const
{
	return name;
}

bool SimplePipe::ConnectClient()
{
	bool isConnected = ConnectNamedPipe(
		hPipe, 
		&overlapped
	);

	if (!isConnected)
	{
		DWORD error = GetLastError();

		if (error == ERROR_PIPE_CONNECTED)
			isConnected = true;
		else if (error == ERROR_IO_PENDING)
		{
			DWORD wait = WaitForSingleObject(
				overlapped.hEvent, 
				timeout
			);

			if (wait == WAIT_OBJECT_0)
			{
				isConnected = GetOverlappedResult(
					hPipe,
					&overlapped,
					nullptr,
					false
				);
			}
			else
			{
				CancelIo(hPipe);
				isConnected = false;
			}
		}
	}

	return isConnected;
}

bool SimplePipe::DisconnectClient()
{
	return DisconnectNamedPipe(hPipe);
}

void SimplePipe::SendNewMessage(Message message)
{
	DWORD sent = 0;

	bool isWritten = WriteFile(
		hPipe,
		&message,
		sizeof(Message),
		&sent,
		&overlapped
	);

	if (!isWritten && GetLastError() == ERROR_IO_PENDING)
	{
		isWritten = GetOverlappedResult(
			hPipe,
			&overlapped,
			&sent,
			true
		);
	}
}

void SimplePipe::ReceiveMessage(Message & message)
{
	DWORD read = 0;

	bool isRead = ReadFile(
		hPipe, 
		&message,
		sizeof(Message), 
		&read, 
		&overlapped
	);
	
	if (!isRead && GetLastError() == ERROR_IO_PENDING)
	{
		isRead = GetOverlappedResult(
			hPipe, 
			&overlapped, 
			&read, 
			true
		);
	}
}

SimplePipe::~SimplePipe()
{
	if (hPipe != nullptr && hPipe != INVALID_HANDLE_VALUE)
	{
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);
	}
}
