/*
* File:		heapsort.c
* Author:	Aaron Rader
* Date:		03/2022
*
* Purpose:	Defines various functions needed to perform a heap sort
*
* Note:		All C code is original, but pseudocode is referenced from:
*			https://gats.ca/home/companions/searching-and-sorting/
*			https://www.geeksforgeeks.org/heap-sort/
*/

#include "sort.h"
#include <stdio.h>

void heapify(double* array, size_t n, size_t i) {
	size_t largest = i;
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;
	
	if (left < n && array[left] > array[largest]) largest = left;
 	if (right < n && array[right] > array[largest]) largest = right;

	if (largest != i) {
		swap(array, i, largest);
		heapify(array, n, largest);
	}
}

void heapsort(double* array, size_t size) {
	for (size_t i = (size - 1) / 2; i > 0; --i)
		heapify(array, size, i);
	heapify(array, size, 0);

	for (size_t i = size - 1; i > 0; --i) {
		swap(array, 0, i);
		heapify(array, i, 0);
	}
}