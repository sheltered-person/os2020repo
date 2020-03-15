//
// Created by sheltered on 05/03/2020.
//

#ifndef CREATORREPORTERPROGRAM_INPUTCLASS_H
#define CREATORREPORTERPROGRAM_INPUTCLASS_H

#include "../Include/Employee.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;


class InputClass
{
public:
    static void InputCreatorParams(string&, int&);

    static void InputReporterParams(string&, int&);
};


#endif //CREATORREPORTERPROGRAM_INPUTCLASS_H
