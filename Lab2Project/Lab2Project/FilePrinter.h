#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Employee.h"

using namespace std;


class FilePrinter
{
public:
	static void PrintBinaryFileReport(ostream&, string);

	static void PrintTextFileReport(ostream&, string);
};

