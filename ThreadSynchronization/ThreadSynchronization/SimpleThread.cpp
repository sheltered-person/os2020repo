#include "SimpleThread.h"


SimpleThread::SimpleThread(ThreadFunc func, LPVOID lpvThreadParam)
{
	this->func = func;
	this->lpvThreadParam = lpvThreadParam;
}


bool SimpleThread::RunThread()
{
	hThread = CreateThread(	NULL, 
							0,
							func, 
							lpvThreadParam, 
							CREATE_SUSPENDED, 
							&dwThreadID);

	if (hThread == NULL)
	{
		free(lpvThreadParam);
		return false;
	}

	SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
	ResumeThread(hThread);

	return true;
}


bool SimpleThread::WaitThread() const
{
	if (WaitForSingleObject(hThread, INFINITE) == WAIT_OBJECT_0)
		return true;

	return false;
}


SimpleThread::~SimpleThread()
{
	CloseHandle(hThread);
}
