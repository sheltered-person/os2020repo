#include "InputProvider.h"


void InputProvider::ReadWorkParams(
	std::string & file, int & recordsCount, int & sendersCount)
{
	std::cout << "Welcome to the receiver process.\n";

	std::cout << "\tEnter binary file name: ";
	std::getline(std::cin, file);

	std::cout << "\tEnter number of records: ";
	std::cin >> recordsCount;

	std::cout << "\tEnter number of senders: ";
	std::cin >> sendersCount;
}


void InputProvider::ReadKey(int & key)
{
	std::cout << "\nChoose the mode:\n"
		<< "\t0. Read message.\n"
		<< "\t1. Exit process.\n";

	std::cin >> key;
}