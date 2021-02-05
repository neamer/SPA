#pragma once

#include "Swap.h"

void BubbleSort(int* arr, int n)
{
	/*
		Bubble sort je najjednostavniji algoritam za sortiranje i
		funkcioniše tako što mjenja susjedne elemente ako su pogrešno
		raspoređeni. Ovaj algoritam ima O(n^2) i u zavisnosti od 
		implementacije može imati isti ili niži best case.

		Ako su urađene optimizacije onda je :
	 
		BEST CASE - kada su svi elementi vec sortirani

		WORST CASE - kada je niz sortiranu u obrnutom redoslijedu	
	*/

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