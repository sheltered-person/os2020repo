#pragma once
#include <Windows.h>


typedef DWORD (_stdcall *ThreadFunc)(LPVOID lpvThreadParam);


class SimpleThread
{
private:
	HANDLE hThread;

	DWORD dwThreadID;

	ThreadFunc func;

	LPVOID lpvThreadParam;

public:
	SimpleThread(ThreadFunc func, LPVOID lpvThreadParam);

	int RunThread();

	unsigned int WaitThread() const;

	virtual ~SimpleThread();
};

