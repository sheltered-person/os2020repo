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


int File::GetPointer() const
{
	int pos = SetFilePointer(
		hFile, 
		0, 
		NULL, 
		FILE_CURRENT
	);

	if (pos == INVALID_SET_FILE_POINTER)
		return -1;

	return pos;
}


void File::SetPointer(int offset)
{
	int pos = SetFilePointer(
		hFile, 
		offset, 
		NULL, 
		FILE_BEGIN
	);
}


void File::WriteBuffer(const void* buffer, int bytesCount, int offset)
{
	if (offset > 0)
		SetPointer(offset);

	WriteFile(
		hFile, 
		buffer, 
		bytesCount, 
		NULL, 
		NULL
	);
}


void File::ReadBuffer(void* buffer, int bytesCount, int offset)
{
	DWORD bytes = 0;

	if (offset >= 0)
		SetPointer(offset);

	ReadFile(
		hFile, 
		buffer, 
		bytesCount, 
		&bytes, 
		NULL
	);
}


int File::FileSize() const
{
	DWORD hightSize;
	return GetFileSize(hFile, &hightSize);
}


File::~File()
{
	CloseHandle(hFile);
}
