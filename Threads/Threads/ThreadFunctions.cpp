#include "ThreadFunctions.h"
#include <limits>
#include <exception>
#include <iostream>


DWORD __stdcall MinMaxThreadFunc(LPVOID lpvParams)
{
	ThreadParams* params = (ThreadParams*)lpvParams;

	params->minPosition = 0;
	params->maxPosition = 0;

	int min = INT_MAX,
		max = INT_MIN;

	for (int i = 0; i < params->size; i++)
	{
		int nextvalue = params->a[i];

		if (nextvalue > max)
		{
			max = nextvalue;
			params->maxPosition = i;
		}

		if (nextvalue < min)
		{
			min = nextvalue;
			params->minPosition = i;
		}

		Sleep(params->sleepInterval);
	}

	return 0;
}


DWORD __stdcall AverageThreadFunc(LPVOID lpvParams)
{
	ThreadParams* params = (ThreadParams*)lpvParams;

	long long sum = 0;

	for (int i = 0; i < params->size; i++)
	{
		sum += params->a[i];
		Sleep(params->sleepInterval);
	}

	params->average = (double)sum / params->size;

	return 0;
}
