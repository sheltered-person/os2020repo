#pragma once
#include <Windows.h>
#include <vector>


typedef struct ThreadParams
{
	int* a;
	int size;

	int sleepInterval;

	unsigned int minPosition;
	unsigned int maxPosition;

	double average;
} ThreadParams;


DWORD WINAPI MinMaxThreadFunc(LPVOID lpvParams);


DWORD WINAPI AverageThreadFunc(LPVOID lpvParams);