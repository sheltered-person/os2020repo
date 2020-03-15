#ifndef CREATORREPORTERPROGRAM_CREATOR_H
#define CREATORREPORTERPROGRAM_CREATOR_H

#include <iostream>
#include <fstream>
#include <limits>

#include "../Include/Employee.h"
#include "../Process Maintaince/RunnableProgram.h"

using namespace std;


class Creator : public RunnableProgram
{
private:
    const static int BUFFER_SIZE = 1024;

    string binaryFileName;

    int entriesAmount;

public:
    Creator(string binaryFileName, int entriesAmount);

    void Run() override ;

    virtual ~Creator();
};

#endif //CREATORREPORTERPROGRAM_CREATOR_H