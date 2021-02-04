#pragma once

#include "Swap.h"

void BubbleSort(int* arr, int n)
{
	bool sorted = false;
	int num_of_passes = 0;
	while (!sorted)
	{
		sorted = true;
		for (size_t i = 0; i < n - num_of_passes - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				Swap(arr[i], arr[i + 1]);
				sorted = false;
			}
		}
	}
}