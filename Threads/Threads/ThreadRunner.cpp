#include "ThreadRunner.h"


int ThreadRunner::Run(int* a, int size)
{
	int thAmount = 2;

	ThreadFunc* functions;
	ThreadParams* params;
	SimpleThread** threads;

	ThreadRunner::InitData(a, size, &threads, &params, &functions, thAmount);

	for (int i = 0; i < thAmount; i++)
	{
		threads[i] = new SimpleThread(functions[i], &params[i]);

		if (threads[i]->RunThread() != 0)
		{
			std::cout << "Thread creation error occured";
			CleanData(threads, params, functions, thAmount);
			return -1;
		}
	}

	for (int i = 0; i < thAmount; i++)
		threads[i]->WaitThread();

	ThreadRunner::ChangeData(a, params);
	return 0;
}


void ThreadRunner::InitData(int* a, int size, SimpleThread*** threads, 
	ThreadParams** params, ThreadFunc** functions, int thAmount)
{
	*functions = new ThreadFunc[thAmount]
	{
		MinMaxThreadFunc,
		AverageThreadFunc
	};

	*params = new ThreadParams[thAmount];
	
	for (int i = 0, t = 7; i < thAmount; i++, t += 5)
	{
		(*params)[i].a = a;
		(*params)[i].size = size;
		(*params)[i].sleepInterval = t;
		(*params)[i].maxPosition = 0;
		(*params)[i].minPosition = 0;
		(*params)[i].average = 0.0;
	}

	*threads = new SimpleThread*[thAmount];
}


void ThreadRunner::ChangeData(int* a, ThreadParams* params)
{
	int minPos = params[0].minPosition,
		maxPos = params[0].maxPosition;

	double average = params[1].average;

	std::cout << "Min value: " << a[minPos] << '\n';
	std::cout << "Max value: " << a[maxPos] << '\n';
	std::cout << "Average value: " << average << '\n';

	a[minPos] = (int)average;
	a[maxPos] = (int)average;
}


void ThreadRunner::CleanData(SimpleThread** threads, ThreadParams* params,
	ThreadFunc* functions, int thAmount)
{
	for (int i = 0; i < thAmount; i++)
		delete threads[i];

	delete[] threads;

	delete[] params;

	delete[] functions;
}