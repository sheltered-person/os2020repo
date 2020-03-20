#include <iostream>
#include <vector>
#include "ThreadRunner.h"


int main()
{
	int size;

	std::cout << "Enter array size (int): ";
	std::cin >> size;

	int* a = new int[size]();

	int thAmount;

	std::cout << "Enter the amount of threads: ";
	std::cin >> thAmount;

	if (ThreadRunner::CreateAndRunThreads(a, size, thAmount) != 0)
	{
		std::cout << "Try again later.\n";
		system("pause");
		return -1;
	}

	int termOne = 0;

	while (thAmount > 0)
	{
		ThreadRunner::WaitThreads();
		ThreadRunner::PrintData(a, size);

		std::cout << "Choose a thread number to terminate: ";
		std::cin >> termOne;

		if (!ThreadRunner::TerminateThread(termOne - 1))
			std::cout << "Couldn't kill Marker!";
		else
			thAmount--;

		ThreadRunner::ResetThreads();
	}

	ThreadRunner::PrintData(a, size);
	ThreadRunner::CleanData();

	std::cout << "\n\n";
	system("pause");
	return 0;
}