#include "ThreadRunner.h"


CRITICAL_SECTION csConsole;
CRITICAL_SECTION csArray;

HANDLE ThreadRunner::hWriteEvent = nullptr;
HANDLE* ThreadRunner::hFinishEvents = nullptr;

ThreadFunc* ThreadRunner::functions = nullptr;
ThreadParams* ThreadRunner::params = nullptr;
SimpleThread** ThreadRunner::threads = nullptr;
HANDLE* ThreadRunner::hContinueEvents = nullptr;
HANDLE* ThreadRunner::hTerminateEvents = nullptr;


int ThreadRunner::thAmount = 0;


int ThreadRunner::InitSyncObjects()
{
	InitializeCriticalSection(&csConsole);
	InitializeCriticalSection(&csArray);

	hWriteEvent = CreateEventA(
		NULL, TRUE, FALSE, NULL);

	if (hWriteEvent == NULL)
		return -1;

	hFinishEvents = new HANDLE[thAmount];
	hContinueEvents = new HANDLE[thAmount];
	hTerminateEvents = new HANDLE[thAmount];

	for (int i = 0; i < thAmount; i++) 
	{
		hFinishEvents[i] = CreateEventA(
			NULL, TRUE, FALSE, NULL);

		if (hFinishEvents[i] == NULL)
			return -2;

		hContinueEvents[i] = CreateEventA(
			NULL, TRUE, FALSE, NULL);

		if (hContinueEvents[i] == NULL)
			return -3;

		hTerminateEvents[i] = CreateEventA(
			NULL, TRUE, FALSE, NULL);

		if (hTerminateEvents[i] == NULL)
			return -3;
	}

	return 0;
}


void ThreadRunner::CleanSyncObjects()
{
	DeleteCriticalSection(&csConsole);
	DeleteCriticalSection(&csArray);

	CloseHandle(hWriteEvent);

	for (int i = 0; i < thAmount; i++)
	{
		CloseHandle(hFinishEvents[i]);
		CloseHandle(hContinueEvents[i]);
		CloseHandle(hTerminateEvents[i]);
	}

	delete[] hFinishEvents;
	delete[] hTerminateEvents;
	delete[] hContinueEvents;
}


int ThreadRunner::CreateAndRunThreads(int* a, int size, int thAmount)
{
	ThreadRunner::thAmount = thAmount;

	if (InitSyncObjects() != 0)
		return -1;

	InitData(a, size);

	for (int i = 0; i < thAmount; i++)
	{
		threads[i] = new SimpleThread(functions[i], &params[i]);

		if (!threads[i]->RunThread())
		{
			std::cout << "Thread creation error occured";

			CleanData();
			CleanSyncObjects();

			return -3;
		}
	}

	SetEvent(hWriteEvent);
	return 0;
}


void ThreadRunner::InitData(int* a, int size)
{
	functions = new ThreadFunc[thAmount];

	for (int i = 0; i < thAmount; i++)
		functions[i] = MarkerThreadFunc;

	params = new ThreadParams[thAmount];

	for (int i = 0; i < thAmount; i++)
	{
		params[i].a = a;
		params[i].size = size;

		params[i].hWriteEvent = hWriteEvent;
		params[i].hFinishEvent = hFinishEvents[i];
		params[i].hContinueEvent = hContinueEvents[i];
		params[i].hTerminateEvent = hTerminateEvents[i];

		params[i].sleepInterval = 5;
		params[i].thNum = i + 1;
	}

	threads = new SimpleThread*[thAmount];
}


bool ThreadRunner::TerminateThread(int i)
{
	if (threads[i] == nullptr)
		return false;

	SetEvent(params[i].hTerminateEvent);
	threads[i]->WaitThread();
	threads[i] = nullptr;

	return true;
}


void ThreadRunner::ResetThreads()
{
	for (int i = 0; i < thAmount; i++)
	{
		if (threads[i] != nullptr)
		{
			ResetEvent(params[i].hFinishEvent);
			SetEvent(params[i].hContinueEvent);
		}
	}
}


void ThreadRunner::PrintData(int * a, int size)
{
	std::cout << "Result array:\n";
	for (int i = 0; i < size; i++)
		std::cout << "\t" << a[i];
	std::cout << "\n";
}


void ThreadRunner::WaitThreads()
{
	WaitForMultipleObjects(thAmount, 
		hFinishEvents, 
		TRUE, 
		INFINITE);
}


int ThreadRunner::CleanData()
{
	CleanSyncObjects();

	for (int i = 0; i < thAmount; i++)
		delete threads[i];

	delete[] threads;

	delete[] params;

	delete[] functions;

	return 0;
}