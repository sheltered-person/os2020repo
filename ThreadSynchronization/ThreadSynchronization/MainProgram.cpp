#include <iostream>
#include <vector>
#include "ThreadRunner.h"


int main()
{
	int size;

	std::cout << "Enter array size (int): ";
	std::cin >> size;

	int* a = new int[size];

	for (int i = 0; i < size; i++)
		a[i] = 0;

	int thAmount;

	std::cout << "Enter the amount of threads: ";
	std::cin >> thAmount;

	ThreadRunner* runner;

	try 
	{
		runner = new ThreadRunner(a, size, thAmount);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << '\n';
		return -1;
	}

	if (runner->CreateAndRunThreads() != 0)
	{
		std::cerr << "Thread creation error occured.\n";
		system("pause");
		return -2;
	}

	int canceledOne = 0;

	while (thAmount > 0)
	{
		runner->WaitThreads();
		runner->PrintData();

		std::cout << "Choose a thread number to cancel: ";
		std::cin >> canceledOne;

		bool isCanceled 
			= runner->TryCancelThread(canceledOne - 1);

		if (!isCanceled)
			std::cout << "Thread ia already cancelled!";
		else
			thAmount--;

		runner->ResetThreads();
	}

	runner->PrintData();

	delete runner;

	std::cout << "\n\n";
	system("pause");

	return 0;
}