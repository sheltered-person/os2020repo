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

	bool WriteMessage(const std::string& message);

	bool RewriteFile();

	int FileSize() const;

	int RecordsCount() const;

	virtual ~File();
};