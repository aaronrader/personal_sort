/*
* File:		selectionsort.c
* Author:	Aaron Rader
* Date:		03/2022
*
* Purpose:	Defines various functions needed to perform a selection sort
*
* Note:		All C code is original, but pseudocode is referenced from:
*			https://gats.ca/home/companions/searching-and-sorting/
*/

#include "sort.h"

void selection_sort(double* array, size_t size) {
	size_t min;
	for (size_t i = 0; i < size - 1; ++i) {
		min = i;
		for (size_t j = i + 1; j < size; ++j) {
			if (array[j] < array[min]) min = j;
		}
		if (min != i)
			swap(array, i, min);
	}
}