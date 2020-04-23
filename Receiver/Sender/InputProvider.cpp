#include "InputProvider.h"

int InputProvider::ChooseMode()
{
	int key = 0;

	std::cout << "Sender process. Choose:" 
		<< "\n\t0. Send message." 
		<< "\n\t1. Exit process.\n";

	std::cin >> key;
	std::cin.ignore();

	return key;
}

std::string InputProvider::ReadMessage()
{
	char message[MESSAGE_SIZE];

	std::cout << "Enter your message: ";
	std::cin.getline(message, MESSAGE_SIZE);

	return std::string(message);
}
