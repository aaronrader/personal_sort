/*
* File:		sort.c
* Author:	Aaron Rader
* Date:		03/2022
*
* Tests various sorting algorithms
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "sort.h"

/*Edit these when adding a new algorithm. Algorithms are declared in sort.h*/
#define NUM_ALGORITHMS 5u
enum algorithms { QUICKSORT, HEAPSORT, BUBBLE_SORT, COCKTAIL_SORT, SELECTION_SORT };
char* algoName[] = { "Quick Sort", "Heap Sort", "Bubble Sort", "Cocktail-Shaker Sort", "Selection Sort" };
void (*sorts[])(double*, size_t) = { quicksort, heapsort, bubble_sort, cocktail_sort, selection_sort };

/*
* Function Name:	is_sorted
* Accepts:			array of type double, size of the array
* Returns:			true if the array is in ascending order
*/
int is_sorted(double* array, size_t size) {
	for (size_t i = 1; i < size; ++i)
		if (array[i] < array[i - 1]) return 0;
	return 1;
}

/*
* Function Name:	print_help
* Purpose:			prints instructions for the program
*/
void print_help() {
	printf(
		"\"sort\" version 0.1, Aaron Rader 2022\n"
		"Usage:\tsort ([-(h|?)]) [filename]\n"
		"\t-h|?\t\thelp\n"
		"\tfilename\tthe name of the file to read\n"
	);
}

int main(int argc, char* argv[]) {
	//program must take in a file name, can not work from console
	if (argc < 2) {
		printf("Error: Too few arguments.\n\n");
		print_help();
		return EXIT_FAILURE;
	}

	int iArgc = 1;
	if (argv[iArgc][0] == '-') {
		char switchChar = argv[iArgc][1];

		//checks the 3rd character of the arg to make sure the switch is only one character
		if (switchChar != 0 && argv[iArgc][2]) {
			printf("Error: Switches contain only one character.\n");
			return EXIT_FAILURE;
		}
		switch (switchChar) {
		case 'h': case'?':
			print_help();
			return EXIT_SUCCESS;
		default:
			printf("Error: Switch not recognized.\n");
			return EXIT_FAILURE;
		}
		++iArgc;
	}

	//regardless of switch, another argument should follow (file name)
	char* fileName;
	if (iArgc < argc) {
		fileName = argv[iArgc];
		++iArgc;
	}
	else {
		printf("Error: Missing file name.\n");
		return EXIT_FAILURE;
	}

	//no arguments expected following the file name
	if (iArgc < argc) {
		printf("Error: Too many command line arguments.\n");
		return EXIT_FAILURE;
	}

	FILE* stream = fopen(fileName, "r");
	if (stream == NULL) {
		printf("Error <%s> ", argv[iArgc - 1]);
		perror(" ");
		return EXIT_FAILURE;
	}

	//Create a dynamic array
	size_t size = 0;
	size_t capacity = 8;
	double* dataset = malloc(capacity * sizeof(double));
	if (dataset == NULL) {
		printf("Error: Memory allocation unsuccessful.\n");
		return EXIT_FAILURE;
	}

	//Read a file into the array
	int ch;
	double value;
	do {
		while ((ch = fscanf(stream, "%lf", &value)) == 1) {
			if (size == capacity) {
				double* temp = realloc(dataset, (capacity *= 2) * sizeof(double));
				if (temp == NULL) {
					printf("Error: Memory allocation unsuccessful.\n");
					free(dataset);
					return EXIT_FAILURE;
				}
				dataset = temp;
			}
			dataset[size++] = value;
		}
		while (ch != EOF && !isspace(fgetc(stream)));
	} while (ch != EOF);

	if (size == 0) {
		printf("Error: File contains no whitespace separated real numbers.\n");
		return EXIT_SUCCESS;
	}
	if (size == 1) {
		printf("Dataset only contains one value.\n");
		return EXIT_SUCCESS;
	}

	/*File Read Complete*/

	//Copy to arrays for each sorting algorithm
	double* sortingArray[NUM_ALGORITHMS];
	for (size_t i = 0; i < NUM_ALGORITHMS; ++i) {
		sortingArray[i] = malloc(size * sizeof(double));
		if (sortingArray[i] == NULL) {
			printf("Error: Memory allocation unsuccessful.\n");
			free(dataset);
			for (size_t j = 0; j < i; ++j)
				free(sortingArray[j]);
			return EXIT_FAILURE;
		}
		for (size_t j = 0; j < size; ++j)
			sortingArray[i][j] = dataset[j];
	}
	free(dataset);

	//Create timers
	clock_t clockCycles;
	clock_t sortClocks[NUM_ALGORITHMS];

	//Output time-to-sort values
	printf("\"sort\" version 1.0 Aaron Rader 2022\n\n");

	printf("Testing sorting algorithms on \"%s\"...\n", fileName);
	printf("Number of elements to sort:\t%zu\n\n", size);

	for (size_t i = 0; i < NUM_ALGORITHMS; ++i) {
		printf("%s\n", algoName[i]);
		clockCycles = clock();
		(*sorts[i])(sortingArray[i], size);
		sortClocks[i] = clock() - clockCycles;
		if (is_sorted(sortingArray[i], size)) printf("Data is sorted.\n");
		printf("Clocks to complete:\t\t%ld (%.3lf seconds)\n", sortClocks[i], (double)sortClocks[i] / CLOCKS_PER_SEC);
		printf("-------------------------------------------------------------------------------\n");
	}

	for (size_t i = 0; i < NUM_ALGORITHMS; ++i) {
		free(sortingArray[i]);
	}

	return EXIT_SUCCESS;
}