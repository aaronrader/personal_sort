/*
* File:		quicksort.c
* Author:	Aaron Rader
* Date:		02/2022
* 
* Purpose:	Defines various functions needed to perform a quick sort
*
* Note:		All C code is original, but pseudocode is referenced from:
*			https://textbooks.cs.ksu.edu/cc310/7-searching-and-sorting/18-quicksort/
*			https://stackoverflow.com/a/39669570/17968700
*			https://gats.ca/home/companions/searching-and-sorting/
*/

#include "sort.h"
#include <assert.h>

size_t partition(double* array, size_t low, size_t high) {
	double pivot = array[(high + low) / 2];
	--low;
	++high;
	while (1) {
		do {
			++low;
		} while (array[low] < pivot);

		do {
			--high;
		} while (array[high] > pivot);

		if (high <= low) return high;
		assert(high > low && "high index is lower than low index");
		swap(array, low, high);
	}
}

void qsort(double* array, size_t low, size_t high) {
	if (low < high) {
		size_t pivot = partition(array, low, high);
		qsort(array, low, pivot);
		qsort(array, pivot + 1, high);
	}
}

void quicksort(double* array, size_t size) {
	qsort(array, 0, size - 1);
}