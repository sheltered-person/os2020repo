#pragma once
#include <iostream>
#include <vector>

#include "SimpleThread.h"
#include "ThreadFunctions.h"


class ThreadRunner
{
public:
	static int Run(int* a, int size);

	static void InitData(int* a, int size, SimpleThread*** threads,
		ThreadParams** params, ThreadFunc** functions, int thAmount);

	static void ChangeData(int* a, ThreadParams* params);

	static void CleanData(SimpleThread** threads, ThreadParams* params,
		ThreadFunc* functions, int thAmount);
};

