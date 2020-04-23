#pragma once
#include <Windows.h>
#include <exception>
#include <string>


class Mutex
{
private:
	HANDLE hMutex;
	Mutex(HANDLE handle);

public:
	static Mutex* Open(const std::string& name);

	Mutex(const std::string & name);

	void Lock();
	void Unlock();

	virtual ~Mutex();
};