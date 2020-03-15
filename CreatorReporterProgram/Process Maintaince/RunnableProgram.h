#ifndef CREATORREPORTERPROGRAM_RUNNABLEPROGRAM_H
#define CREATORREPORTERPROGRAM_RUNNABLEPROGRAM_H

#include <fstream>

using namespace std;


class RunnableProgram
{
public:
    virtual void Run() = 0;

    virtual ~RunnableProgram() { }
};


#endif //CREATORREPORTERPROGRAM_RUNNABLEPROGRAM_H
