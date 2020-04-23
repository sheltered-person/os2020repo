#include <iostream>
#include <Windows.h>
#include <string>

#include "InputProvider.h"
#include "Names.h"
#include "File.h"
#include "Mutex.h"


void WaitAccess(Mutex* mutex, File* file)
{
	int fileSize = file->FileSize();
	int fileRecordsCount = file->RecordsCount();

	while (fileSize == MESSAGE_SIZE * fileRecordsCount)
	{
		mutex->Unlock();
		Sleep(1000);

		mutex->Lock();
		fileSize = file->FileSize();
	}
}


void DoSenderWork(Mutex* mutex, File* file)
{
	int key;

	while (true)
	{
		key = InputProvider::ChooseMode();

		if (key)
			return;
		else
		{
			std::string message = InputProvider::ReadMessage();

			mutex->Lock();
			WaitAccess(mutex, file);

			file->WriteMessage(message);
			mutex->Unlock();
		}
	}
}


int main(int argc, char* argv[])
{
	const std::string fileName = argv[0];
	int recordsCount = std::strtol(argv[1], nullptr, 10);
	const auto pid = GetCurrentProcessId();

	const auto hEvent = OpenEvent(
		EVENT_MODIFY_STATE, 
		FALSE, 
		(eventName + std::to_string(pid)).c_str()
	);

	if (hEvent == nullptr)
	{
		std::cerr << "Error: can not open event (error " 
			+ std::to_string(GetLastError()) + ").";
		return 1;
	}

	SetEvent(hEvent);

	File* file;
	Mutex* mutex;

	try
	{
		file = new File(fileName, recordsCount);
		mutex = Mutex::Open(mutexName);
	}
	catch (const std::exception& ex)
	{
		CloseHandle(hEvent);

		std::cerr << ex.what() << std::endl;
		return 2;
	}

	DoSenderWork(mutex, file);

	delete file;
	delete mutex;

	return 0;
}