#include "ProcessMaintainer.h"

const int BUFFER_SIZE = 1024;


void ProcessMaintainer::Run()
{
	//Creator params.

	string binaryFileName;
	binaryFileName.reserve(BUFFER_SIZE);

	int entriesAmount;
	InputParamClass::InputCreatorParams(binaryFileName, entriesAmount);


	//Creator calling.

	LPCSTR lpcCreatorPath = "D:\\bsu\\OS\\Creator\\Debug\\Creator.exe";

	string commandLine;
	commandLine.reserve(BUFFER_SIZE);

	commandLine.append(lpcCreatorPath);
	commandLine.append(" ");
	commandLine.append(binaryFileName);
	commandLine.append("  " + to_string(entriesAmount));

	CreateProcessParams(lpcCreatorPath, (LPSTR)commandLine.c_str());
	FilePrinter::PrintBinaryFileReport(cout, binaryFileName);


	//Reporter params.

	string reportFileName;
	reportFileName.reserve(BUFFER_SIZE);

	int salary;
	InputParamClass::InputReporterParams(reportFileName, salary);


	//Reporter calling.

	LPCSTR lpcReporterPath = "D:\\bsu\\OS\\Reporter\\Debug\\Reporter.exe";

	commandLine = lpcReporterPath;
	commandLine.append(" ");
	commandLine.append(binaryFileName);
	commandLine.append(" ");
	commandLine.append(reportFileName);
	commandLine.append(" " + to_string(salary));

	CreateProcessParams(lpcReporterPath, (LPSTR)commandLine.c_str());
	FilePrinter::PrintTextFileReport(cout, reportFileName);
}


bool ProcessMaintainer::CreateProcessParams(LPCSTR lpcPath, LPSTR lpCommandLine)
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;

	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&processInfo, sizeof(processInfo));

	if (!CreateProcessA(
		lpcPath,               //��� ������������ �����.
		lpCommandLine,         //��������� ������.
		NULL,                  //�������� ������������ ��������.
		NULL,                  //�������� ������������ ���������� ������.
		FALSE,                 //������������ ����������.
		0,                     //���� ��������.
		NULL,                  //����� ����� ������ �������� (���������� ���������, ������ � ��.) �� ���������.
		NULL,                  //������� ������� ������ �������� (��� ��, ��� � � ��������).
		&startupInfo,		   //���������� ��� �������� ������ ��������.
		&processInfo))		   //���������, ���������� ���������� �� �������� �������� (�������� ��������).
	{
		cout << "CreateProcess failed (" << GetLastError() << ").\n";
		return false;
	}

	WaitForSingleObject(processInfo.hProcess, INFINITE);

	DWORD dwExitCode;

	if (!GetExitCodeProcess(processInfo.hProcess, &dwExitCode))
	{
		cout << "GetExitCodeProcess failed (" << GetLastError() << ").\n";
		return false;
	}

	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);

	return true;
}
