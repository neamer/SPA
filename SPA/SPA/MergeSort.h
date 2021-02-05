#pragma once

void Merge(int* arr, int* temp, int start1, int start2, int end1, int end2)
{
	int counter1 = start1, counter2 = start2, temp_counter = start1;

	while (counter1 < end1 && counter2 < end2)
	{
		if (arr[counter1] < arr[counter2])
			temp[temp_counter++] = arr[counter1++];		
		else
			temp[temp_counter++] = arr[counter2++];
	}

	while(counter1 < end1)
		temp[temp_counter++] = arr[counter1++];
	while (counter2 < end2)
		temp[temp_counter++] = arr[counter2++];

	for (size_t i = start1; i < end2; i++)
		arr[i] = temp[i];
}

void MergeSort(int* arr, int* temp, int start, int end)
{
	if (end - start > 1)
	{
		int middle = start + (end - start) / 2;
		MergeSort(arr, temp, start, middle);
		MergeSort(arr, temp, middle, end);
		Merge(arr, temp, start, middle, middle, end);
	}
}