#include "File.h"


File::File(const std::string & name, int recordsCount)
{
	hFile = CreateFile(
		LPCSTR(name.c_str()),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);

	if (hFile == INVALID_HANDLE_VALUE)
		throw "Error: file creation failed (error "
		+ std::to_string(GetLastError()) + ").";

	this->recordsCount = recordsCount;
}


bool File::NextMessage(std::string& message) const
{
	const DWORD fSize = GetFileSize(hFile, nullptr);
	char cMessage[MESSAGE_SIZE];

	SetFilePointer(hFile, 0, nullptr, FILE_BEGIN);

	if (fSize == 0ul)
	{
		std::cerr << "\nFile is empty";
		return false;
	}
	else
	{
		BOOL isRead = ReadFile(
			hFile,
			cMessage,
			MESSAGE_SIZE,
			nullptr,
			nullptr
		);

		if (!isRead)
			throw "File read function failed (error " +
			std::to_string(GetLastError()) + ").";
	}

	message = cMessage;
	return true;
}


bool File::WriteMessage(const std::string & message)
{
	SetFilePointer(hFile, 0, nullptr, FILE_END);

	BOOL isWriten = WriteFile(
		hFile, 
		message.c_str(), 
		MESSAGE_SIZE, 
		nullptr, 
		nullptr
	);

	return isWriten;
}


bool File::RewriteFile()
{
	char* fileContents = new char[MESSAGE_SIZE * recordsCount];
	char* currentLine = new char[MESSAGE_SIZE];

	int linesCount = 0;
	DWORD readBytesCount = -1;

	while (true)
	{
		if (!ReadFile(hFile, currentLine, MESSAGE_SIZE, &readBytesCount, nullptr))
		{
			std::cout << "error of reading";
			return false;
		}

		if (readBytesCount == 0)
			break;

		memcpy_s(fileContents + MESSAGE_SIZE * linesCount, 
			MESSAGE_SIZE, currentLine, MESSAGE_SIZE);

		linesCount++;
	}

	SetFilePointer(hFile, 0, nullptr, FILE_BEGIN);
	WriteFile(hFile, fileContents, linesCount * MESSAGE_SIZE, nullptr, nullptr);
	SetEndOfFile(hFile);

	return true;
}


int File::FileSize() const
{
	DWORD hightSize;
	return GetFileSize(hFile, &hightSize);
}


int File::RecordsCount() const
{
	return recordsCount;
}


File::~File()
{
	CloseHandle(hFile);
}
