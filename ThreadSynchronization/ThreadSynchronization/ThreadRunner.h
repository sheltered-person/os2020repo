#pragma once
#include <iostream>
#include <vector>

#include "SimpleThread.h"
#include "ThreadFunctions.h"


class ThreadRunner
{
private:
	static HANDLE hWriteEvent;
	static HANDLE* hFinishEvents;
	static HANDLE* hContinueEvents;
	static HANDLE* hTerminateEvents;

	static ThreadFunc* functions;
	static ThreadParams* params;
	static SimpleThread** threads;

	static int thAmount;

public:
	static int InitSyncObjects();

	static void CleanSyncObjects();

	static int CreateAndRunThreads(int* a, int size, int thAmount);

	static void InitData(int* a, int size);

	static void WaitThreads();

	static void PrintData(int*a, int size);

	static bool TerminateThread(int i);

	static void ResetThreads();

	static int CleanData();
};

