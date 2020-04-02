#include "ThreadFunctions.h"

#include <limits>
#include <exception>
#include <iostream>
#include <vector>


extern CRITICAL_SECTION csConsole;
extern CRITICAL_SECTION csArray;


bool ModifyElement(int* a, int i, int newValue, int sleepInterval)
{
	bool result = false;

	EnterCriticalSection(&csArray);

	if (a[i] == 0)
	{
		Sleep(sleepInterval);

		a[i] = newValue;
		result = true;

		Sleep(sleepInterval);
	}

	LeaveCriticalSection(&csArray);
	return result;
}


void PrintReport(int thNum, int markCount, int lastValue)
{
	EnterCriticalSection(&csConsole);

	std::cout << "Thread No. " << thNum << " finish, " <<
		markCount << " elements are marked, " <<
		lastValue + 1 << " element stopped the thread.\n";

	LeaveCriticalSection(&csConsole);
}


void PrintTerminationMessage(int thNum)
{
	EnterCriticalSection(&csConsole);
	std::cout << "Thread " << thNum << " is terminated.\n";
	LeaveCriticalSection(&csConsole);
}


void RestoreArray(int* a, int size, std::vector<int> marked)
{
	EnterCriticalSection(&csArray);

	for (int i : marked)
		a[i] = 0;

	LeaveCriticalSection(&csArray);
}


DWORD __stdcall MarkerThreadFunc(LPVOID lpvParams)
{
	ThreadParams* params = (ThreadParams*)lpvParams;

	DWORD dwWaitResult = WaitForSingleObject(
		params->hWriteEvent,
		INFINITE);

	if (dwWaitResult != WAIT_OBJECT_0)
		return false;

	int thNum = params->thNum;
	int markCount = 0;

	std::vector<int> marked(params->size);

	srand(thNum);

	while (true)
	{
		ResetEvent(params->hContinueEvent);

		int nextValue = rand() % params->size;
		bool isMarked = ModifyElement(
							params->a,
							nextValue,
							thNum,
							params->sleepInterval);		

		if (isMarked)
		{
			marked.push_back(nextValue);
			markCount++;
		}
		else
		{
			PrintReport(thNum, markCount, nextValue);
			SetEvent(params->hFinishEvent);

			HANDLE hAvaitableEvents[2] = { 
				params->hTerminateEvent,
				params->hContinueEvent
			};

			dwWaitResult = WaitForMultipleObjects(2,
				hAvaitableEvents,
				FALSE,
				INFINITE);

			if (dwWaitResult == WAIT_OBJECT_0)
			{
				RestoreArray(params->a, params->size, marked);
				PrintTerminationMessage(thNum);

				return 0;
			}
		}
	}
}