#pragma once
#include <iostream>
#include <Windows.h>
#include <exception>
#include <string>

#include "Names.h"


class File
{
private:
	HANDLE hFile;

	std::string name;
	int recordsCount;

public:
	File(const std::string& name, int recordsCount);

	bool NextMessage(std::string& meassage) const;

	bool RewriteFile();

	int FileSize() const;

	virtual ~File();
};

