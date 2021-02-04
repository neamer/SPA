#pragma once

void InsertionSort(int* arr, int n)
{
	/*
		Niz logicki djelimo na sortirani i nesortirani dio,
		na pocetku izvrsavanja sortirani dio je prvi element
		a nesortirani je ostatak niza. Svaki prolaz petlje dodajemo
		novi element u sortirani dio i pronalazimo njegovo mjesto.
	*/

	for (size_t i = 1; i < n; i++)
	{
		int element = arr[i];

		int j = i;
		while (j > 0 && element < arr[j-1])
		{
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = element;
	}
}

void InsertionSortAlt(int* arr, int n)
{
	//adilov nacin

	for (size_t i = 1; i < n; i++)
	{
		int j = i;
		
		while (j > 0 && arr[j - 1] > arr[j])
		{
			int element = arr[j]; // adilov naziv - pom??
			arr[j] = arr[j - 1];
			arr[j - 1] = element;
			j--;
		}
	}
}