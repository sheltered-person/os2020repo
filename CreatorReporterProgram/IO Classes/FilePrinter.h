#ifndef CREATORREPORTERPROGRAM_FILEPRINTER_H
#define CREATORREPORTERPROGRAM_FILEPRINTER_H

#include "../Include/Employee.h"
#include <iostream>
#include <fstream>

using namespace std;


class FilePrinter
{
public:
    static void PrintBinaryFileReport(ostream&, string);

    static void PrintTextFileReport(ostream&, string);
};;


#endif //CREATORREPORTERPROGRAM_FILEPRINTER_H
