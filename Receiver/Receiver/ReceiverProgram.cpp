#include <iostream>
#include <Windows.h>
#include <string>

#include "Names.h"
#include "InputProvider.h"
#include "SimpleProcess.h"
#include "File.h"
#include "Mutex.h"


void DoReceiverWork(Mutex* mutex, File* file)
{
	int key;
	std::string message;

	while (true)
	{
		InputProvider::ReadKey(key);

		if (key)
			return;
		else
		{
			mutex->Lock();

			if (!file->NextMessage(message))
				continue;

			std::cout << message << "\n";

			if (!file->RewriteFile())
				continue;

			mutex->Unlock();
		}
	}
}


int main()
{
	std::string fileName;

	int sendersCount = 0;
	int recordsCount = 0;

	InputProvider::ReadWorkParams(fileName, recordsCount, sendersCount);

	File* file;
	Mutex* mutex;

	try
	{
		file = new File(fileName, recordsCount);
		mutex = new Mutex(mutexName);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	};

	HANDLE* hEvents = new HANDLE[sendersCount];
	SimpleProcess** processes = new SimpleProcess*[sendersCount];

	try
	{
		for (int i = 0; i < sendersCount; i++)
		{
			std::string commandLine(fileName + " " + std::to_string(recordsCount));
			processes[i] = new SimpleProcess(senderPath, commandLine);
			int pid = processes[i]->GetProcessID();

			hEvents[i] = CreateEvent(
				nullptr,
				TRUE,
				FALSE,
				LPSTR((eventName + std::to_string(pid)).c_str())
			);
		}
	}
	catch (const std::exception& ex)
	{
		for (int i = 0; i < sendersCount; i++)
			CloseHandle(hEvents[i]);

		delete[] hEvents;
		delete[] processes;

		delete file;
		delete mutex;

		std::cerr << ex.what() << std::endl;
		return 2;
	}

	WaitForMultipleObjects(sendersCount, hEvents, TRUE, INFINITE);
	DoReceiverWork(mutex, file);

	delete file;
	delete mutex;

	for (int i = 0; i < sendersCount; i++)
		CloseHandle(hEvents[i]);

	delete[] hEvents;
	delete[] processes;

	return 0;
}