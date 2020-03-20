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

	bool RunThread();

	bool WaitThread() const;

	virtual ~SimpleThread();
};

