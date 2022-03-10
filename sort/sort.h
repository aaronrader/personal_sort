/*
* File:		sort.h
* Author:	Aaron Rader
* Date:		02/2022
*
* Purpose:	Declares various sorting functions
*/

#include <stddef.h>

#ifndef SORT_H_
#define SORT_H_
inline void swap(double* array, size_t a, size_t b) {
	double temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

void quicksort(double* array, size_t size);
void heapsort(double* array, size_t size);
void bubble_sort(double* array, size_t size);
void cocktail_sort(double* array, size_t size);
void selection_sort(double* array, size_t size);
#endif