#include "FilePrinter.h"


void FilePrinter::PrintBinaryFileReport(ostream& out, string binaryFileName)
{
    ifstream bin(binaryFileName, ios::binary);
    int entriesAmount;

    if (!bin.is_open())
    {
        out << "Error: binary file can't be opened.\n\n";
        return;
    }

    bin >> entriesAmount;

    out << "\nBinary file content:\n\n" << "Num\tName\tHours\n\n";

    for (int i = 0; i < entriesAmount; i++)
    {
        Employee employee;
        bin >> employee.num >> employee.name >> employee.hours;

        out << employee.num << "\t" << employee.name << "\t" << employee.hours << "\n";
    }

    bin.close();
}


void FilePrinter::PrintTextFileReport(ostream &out, string reportFileName)
{
    ifstream fin(reportFileName);

    if (!fin.is_open())
    {
        out << "Error: text report file can't be opened.\n\n";
        return;
    }

    out << "\nReport text file contents:\n\n";

    string reportString;

    while (!fin.eof())
    {
        getline(fin, reportString);
        out << reportString << "\n";
    }

    fin.close();
}