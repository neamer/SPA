#pragma once

#include "Swap.h"

void SelectionSort(int* arr, int n)
{
	/*
		Niz ponovo logički dijelimo na nesortirani i sortirani
		podniz. U svakoj iteraciji nalazimo najmanji element iz
		nesortiranog podniza i stavimo ga na kraj sortiranog.
		Uvijek moramo provjeriti cijeli niz da bi znali koji je
		najmanji element iz nesortiranog podniza tako da je
		vrijeme izvršavanja uvijek n^2
	*/
	for (size_t i = 0; i < n - 1; i++)
	{
		int min_index = i;

		for (size_t j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_index])
				min_index = j;
		}

		if(min_index != i)
			Swap(arr[min_index], arr[i]);
	}
}