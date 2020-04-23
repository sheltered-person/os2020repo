#pragma once
#include <iostream>
#include <string>

#include "Names.h"


class InputProvider
{
public:
	static int ChooseMode();

	static std::string ReadMessage();
};

