#pragma once
#include <iostream>
#include <Windows.h>
#include <exception>
#include <string>

#include "ServerNames.h"


class File
{
private:
	HANDLE hFile;

	std::string name;
	int recordsCount;

public:
	File(const std::string& name, int recordsCount);

	int GetPointer() const;
	void SetPointer(int offset);

	void WriteBuffer(const void* buffer, int bytesCount, int offset);
	void ReadBuffer(void* buffer, int bytesCount, int offset);

	int FileSize() const;

	virtual ~File();
};

