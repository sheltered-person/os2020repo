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
		lpcPath,               //Имя исполняемого файла.
		NULL,                  //Командная строка.
		NULL,                  //Атрибуты безопасности процесса.
		NULL,                  //Атрибуты безопасности первичного потока.
		FALSE,                 //Наследование описателей.
		0,                     //Флаг создания.
		NULL,                  //Адрес блока памяти процесса (переменные окружения, строки и др.) по умолчанию.
		NULL,                  //Рабочий каталог нового процесса (тот же, что и у родителя).
		&startupInfoStruct,    //Информация для создания нового процесса.
		&processInfoStruct))   //Структура, получающая информацию об открытом процессе (выходной параметр).
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