#include <iostream>
#include <time.h>

#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "Heap.h"

#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"

const char* crt = "\n>========================================<\n";

void PrintArray(int* arr, int n)
{
	for (size_t i = 0; i < n; i++)
	{
		std::cout << arr[i] << "\t";
	}
}

void FillArray(int* arr, int n)
{
	for (size_t i = 0; i < n; i++)
	{
		arr[i] = rand() % 1000 + 1;
	}
}

void TestSort()
{
	srand(time(NULL));

	int size;

	std::cout << "Velicina niza -> ";
	std::cin >> size;

	int* arr = new int[size];

	FillArray(arr, size);

	PrintArray(arr, size);
	std::cout << crt;

	/*	In-place  */
	//BubbleSort(arr, size);
	//InsertionSort(arr, size);
	//SelectionSort(arr, size);

	/*  Divide & Conquer  */
	int* temp = new int[size];
	MergeSort(arr, temp, 0, size);

	PrintArray(arr, size);
}

int main()
{
	//TestStack();
	//TestQueue();
	//TestPriorityQueue();
	//TestHeap();

	TestSort();

	return 0;
}