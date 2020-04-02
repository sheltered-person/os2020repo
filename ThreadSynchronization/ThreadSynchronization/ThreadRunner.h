#pragma once
#include <iostream>
#include <vector>

#include "SimpleThread.h"
#include "ThreadFunctions.h"


class ThreadRunner
{
private:
	HANDLE hWriteEvent;
	HANDLE* hFinishEvents;
	HANDLE* hContinueEvents;
	HANDLE* hCancellationEvents;

	ThreadFunc* functions;
	ThreadParams* params;
	SimpleThread** threads;

	int* a;
	int size;

	int thAmount;

	int InitSyncObjects();
	void CleanSyncObjects();

	void InitData();
	int CleanData();

public:
	ThreadRunner(int* a, int size, int thAmount);

	int CreateAndRunThreads();

	void WaitThreads();

	void PrintData() const;

	bool TryCancelThread(int i);

	void ResetThreads();

	virtual ~ThreadRunner();
};

