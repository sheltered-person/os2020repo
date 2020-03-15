#include "Creator.h"


Creator::Creator(string binaryFileName, int entriesAmount)
{
    this->binaryFileName = binaryFileName;
    this->entriesAmount = entriesAmount;
}


void Creator:: Run()
{
    ofstream out(binaryFileName, ios::binary);

    cout<<"\n\nWelcome to the creator plugin!\n\n";
    out << entriesAmount << "\n";

    for (int i = 0; i < entriesAmount; i++)
    {
        Employee employee;
        cout << "\tEnter employee id number: ";

        while (!(cin >> employee.num))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\tInput error. Try again: ";
        }

        cout << "\tEnter employee name: ";

        cin.ignore();
        cin.getline(employee.name, BUFFER_SIZE);

        cout << "\tEnter employee working hours: ";

        while (!(cin >> employee.hours))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\tInput error. Try again: ";
        }

        out << employee.num << "\t" << employee.name << "\t" << employee.hours << "\n";
    }

    out.close();
}

Creator::~Creator() { }
