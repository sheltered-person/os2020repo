#include <Windows.h>
#include <stdio.h>


int main()
{
	LPCSTR lpcPath = "D:\\bsu\\OS\\ProcessB\\Debug\\ProcessB.exe";

	STARTUPINFO startupInfoStruct;
	PROCESS_INFORMATION processInfoStruct;

	ZeroMemory(&startupInfoStruct, sizeof(startupInfoStruct));
	startupInfoStruct.cb = sizeof(startupInfoStruct);
	ZeroMemory(&processInfoStruct, sizeof(processInfoStruct));

	if (!CreateProcessA(
		lpcPath,               //��� ������������ �����.
		NULL,                  //��������� ������.
		NULL,                  //�������� ������������ ��������.
		NULL,                  //�������� ������������ ���������� ������.
		FALSE,                 //������������ ����������.
		0,                     //���� ��������.
		NULL,                  //����� ����� ������ �������� (���������� ���������, ������ � ��.) �� ���������.
		NULL,                  //������� ������� ������ �������� (��� ��, ��� � � ��������).
		&startupInfoStruct,    //���������� ��� �������� ������ ��������.
		&processInfoStruct))   //���������, ���������� ���������� �� �������� �������� (�������� ��������).
	{
		printf("CreateProcess (process A) failed (%d).\n", GetLastError());
		system("pause");
		return -1;
	}

	CloseHandle(processInfoStruct.hThread);
	CloseHandle(processInfoStruct.hProcess);

	system("pause");
	return 0;
}