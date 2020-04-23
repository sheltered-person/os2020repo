#pragma once
#include <iostream>
#include <string>


class InputProvider
{
public:
	static void ReadWorkParams(std::string& file, int& recordsCount, int& sendersCount);

	static void ReadKey(int& key);
};
