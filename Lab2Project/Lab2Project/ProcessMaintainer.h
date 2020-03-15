#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

#include "Employee.h"
#include "FilePrinter.h"
#include "InputParamClass.h"

using namespace std;


class ProcessMaintainer
{
public:
	static void Run();

	static bool CreateProcessParams(LPCSTR, LPSTR);
};

