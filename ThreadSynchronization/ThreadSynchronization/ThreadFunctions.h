#pragma once
#include <Windows.h>
#include <vector>


typedef struct ThreadParams
{
	int* a;
	int size;

	HANDLE hWriteEvent;
	HANDLE hFinishEvent;
	HANDLE hContinueEvent;
	HANDLE hTerminateEvent;

	int sleepInterval;
	int thNum;
} ThreadParams;


DWORD WINAPI MarkerThreadFunc(LPVOID lpvParams);