#include "Mutex.h"


Mutex::Mutex(HANDLE handle)
{
	hMutex = handle;
}


Mutex* Mutex::Open(const std::string & name)
{
	HANDLE handle = OpenMutex(
		MUTEX_ALL_ACCESS,
		FALSE,
		name.c_str()
	);

	if (handle == NULL)
		throw "Error: mutex open function failed.";

	Mutex m(handle);
	return &m;
}


Mutex::Mutex(const std::string & name)
{
	hMutex = CreateMutex(
		nullptr,
		FALSE,
		name.c_str()
	);

	if (hMutex == NULL)
		throw "Error: mutex creation failed (error " +
		std::to_string(GetLastError()) + ").";
}


void Mutex::Lock()
{
	WaitForSingleObject(hMutex, INFINITE);
}


void Mutex::Unlock()
{
	ReleaseMutex(hMutex);
}


Mutex::~Mutex()
{
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
}