#include <iostream>
#include <string>

#include "IO Classes/FilePrinter.h"
#include "IO Classes/InputClass.h"

#include "Process Maintaince/ProcessMaintainer.h"

#include "Creation/Creator.h"
#include "Reporting/Reporter.h"
#include "IO Classes/InputClass.h"

int main() {
    const int BUFFER_SIZE = 1024;

    string binaryFileName;
    binaryFileName.reserve(BUFFER_SIZE);

    int entriesAmount;
    InputClass::InputCreatorParams(binaryFileName, entriesAmount);

    Creator* creator = new Creator(binaryFileName, entriesAmount);

    ProcessMaintainer* maintainer = new ProcessMaintainer(creator);

    if (maintainer->Run() != 0)
        return -1;

    FilePrinter::PrintBinaryFileReport(cout, binaryFileName);

    string reportFileName;
    reportFileName.reserve(BUFFER_SIZE);

    int salary;
    InputClass::InputReporterParams(reportFileName, salary);

    Reporter* reporter = new Reporter(binaryFileName, reportFileName, salary);
    maintainer = new ProcessMaintainer(reporter);

    if (maintainer->Run() != 0)
        return -2;

    FilePrinter::PrintTextFileReport(cout, reportFileName);

    delete creator;
    delete maintainer;
    delete reporter;

    return 0;;
}
