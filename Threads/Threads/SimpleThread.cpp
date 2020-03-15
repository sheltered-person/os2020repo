#include "SimpleThread.h"


SimpleThread::SimpleThread(ThreadFunc func, LPVOID lpvThreadParam)
{
	this->func = func;
	this->lpvThreadParam = lpvThreadParam;
}


int SimpleThread::RunThread()
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
		return -1;
	}

	SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
	ResumeThread(hThread);

	return 0;
}


unsigned int SimpleThread::WaitThread() const
{
	return WaitForSingleObject(hThread, INFINITE);
}


SimpleThread::~SimpleThread()
{
	CloseHandle(hThread);
}
