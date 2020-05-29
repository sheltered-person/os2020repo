#pragma once
#include <Windows.h>


class CriticalSection
{
private:
	CRITICAL_SECTION cSection;

public:
	CriticalSection();

	void EnterSection();
	void LeaveSection();

	virtual ~CriticalSection();
};

