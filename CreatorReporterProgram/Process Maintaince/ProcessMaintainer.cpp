#include "ProcessMaintainer.h"


ProcessMaintainer::ProcessMaintainer(RunnableProgram* program)
{
    this->program = program;
}


int ProcessMaintainer::Run()
{
    pid = fork();

    if (pid < 0)
        return -1;
    else if (pid == 0)
        program->Run();
    else {
        int status;

        if (waitpid(pid, &status, 0) == -1)
            return -1;
        else
        {
            if (WIFEXITED(status))
            {
                if (WEXITSTATUS(status) != 0)
                    return -2;
            }
            else if (WIFSIGNALED(status))
                return -3;
        }
    }

    return 0;
}


ProcessMaintainer::~ProcessMaintainer() { }


