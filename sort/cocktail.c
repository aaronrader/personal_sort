/*
* File:		cocktail.c
* Author:	Aaron Rader
* Date:		03/2022
*
* Purpose:	Defines various functions needed to perform a cocktail-shaker sort
*
* Note:		All C code is original, but pseudocode is referenced from:
*			https://gats.ca/home/companions/searching-and-sorting/
*/

#include "sort.h"

void cocktail_sort(double* array, size_t size) {
	if (size < 2) return;
	size_t left = 0;
	size_t right = size - 1;
	size_t current = 0;
	while (left < right) {
		while (current < right) {
			if (array[current] > array[current + 1]) swap(array, current, current + 1);
			++current;
		}
		--right;
		while (current > left) {
			if (array[current] < array[current - 1]) swap(array, current, current - 1);
			--current;
		}
		++left;
	}
}