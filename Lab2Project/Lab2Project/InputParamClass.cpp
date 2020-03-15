#include "InputParamClass.h"


void InputParamClass::InputCreatorParams(string& binaryFileName, int &entriesAmount)
{
	cout << "\tEnter binary file name: ";
	getline(cin, binaryFileName);

	cout << "\tEnter the amount of entries: ";

	while (!(cin >> entriesAmount))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\tInput error. Try again: ";
	}
}


void InputParamClass::InputReporterParams(string& reportFileName, int& salary)
{
	cout << "\n\tEnter report file name: ";

	cin.ignore();
	getline(cin, reportFileName);

	cout << "\tEnter salary for 1 hour: ";

	while (!(cin >> salary))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\tInput error. Try again: ";
	}
}
