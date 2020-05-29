#include "CriticalSection.h"

CriticalSection::CriticalSection()
{
	InitializeCriticalSection(&cSection);
}

void CriticalSection::EnterSection()
{
	EnterCriticalSection(&cSection);
}

void CriticalSection::LeaveSection()
{
	LeaveCriticalSection(&cSection);
}

CriticalSection::~CriticalSection()
{
	DeleteCriticalSection(&cSection);
}
