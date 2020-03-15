#ifndef CREATORREPORTERPROGRAM_PROCESSMAINTAINER_H
#define CREATORREPORTERPROGRAM_PROCESSMAINTAINER_H

#include <iostream>
#include <string>

#include <unistd.h>
#include <wait.h>

#include "RunnableProgram.h"

using namespace std;


class ProcessMaintainer
{
private:
    RunnableProgram* program;

    pid_t pid;


public:
    ProcessMaintainer(RunnableProgram* program);

    int Run();

    virtual ~ProcessMaintainer();
};


#endif //CREATORREPORTERPROGRAM_PROCESSMAINTAINER_H
