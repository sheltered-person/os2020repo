#include <iostream>
#include <vector>
#include "ThreadRunner.h"


int main()
{
	int size;

	std::cout << "Enter array size (int): ";
	std::cin >> size;

	std::cout << "Enter the array of " << size << " integers:\n\t";

	int* a = new int[size];

	for (int i = 0; i < size; i++)
		std::cin >> a[i];

	if (ThreadRunner::Run(a, size) != 0)
	{
		std::cout << "Try again later.\n";
		system("pause");
		return -1;
	}

	std::cout << "\nResult:\n\t";

	for (int i = 0; i < size; i++)
		std::cout << a[i] << " ";

	std::cout << "\n\n";
	system("pause");
	return 0;
}