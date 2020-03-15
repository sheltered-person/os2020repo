#ifndef CREATORREPORTERPROGRAM_REPORTER_H
#define CREATORREPORTERPROGRAM_REPORTER_H

#include <iostream>
#include <fstream>

#include "SalaryCounter.h"
#include "../Process Maintaince/RunnableProgram.h"

using namespace std;


class Reporter : public RunnableProgram
{
private:
    string binarySource,
        reportFileName;

    int salaryForHour;

public:
    Reporter(string binarySource, string reportFileName, int salaryForHour);

    void Run() override ;

    virtual ~Reporter();
};


#endif //CREATORREPORTERPROGRAM_REPORTER_H
