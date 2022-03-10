/*
* File:		bubblesort.c
* Author:	Aaron Rader
* Date:		03/2022
*
* Purpose:	Defines various functions needed to perform a bubble sort
*
* Note:		All C code is original, but pseudocode is referenced from:
*			https://gats.ca/home/companions/searching-and-sorting/
*/

#include "sort.h"

void bubble_sort(double* array, size_t size) {
	int hasSwapped;
	for (size_t i = 0; i < size; ++i) {
		hasSwapped = 0;
		for (size_t j = 0; j < size - 1 - i; ++j) {
			if (array[j] > array[j + 1]) {
				swap(array, j, j + 1);
				hasSwapped = 1;
			}
		}
		if (!hasSwapped) return;
	}
}