/**
 * 	@file sorting.cpp
 * 	@author Sheng-Hao Ma (aaaddress1, aka adr)
 * 	@date 02/15/2017
 * 	@brief implementat sorting algoprithms
 **/
#include <stdio.h>
#include <iterator>
#include <time.h>
#define swap(type, x, y) do{ type buff = x; x = y; y = buff; } while(0)
#define calcTime(msg, body) { clock_t b = clock(); body; printf(msg, ((float)(clock() - b)/CLOCKS_PER_SEC)); }

void printArr(/* output array */int *a, /* count */size_t n) {
	for(size_t i = 0; i < n; printf("%d ", a[i]), i++);
	puts("");
}

/* Selection Sorting */
void selectSort(/* input array */int *a, /* count */size_t n) {
	for(int i = 0, j = 0, p = 0; i < n - 1; i++) {
		p = i;
		for(j = i + 1; j < n; p = a[p] < a[j] ? p : j, j++);
		swap(int, a[p], a[i]);
	}
}

/* Merge Sorting */

int* genDataArr(int &count) {
	static int n = 5; //array length
	static int darr[] = {1, 7, 3, 2, 5}; //input array data
	int *narr = new int[n];
	for (int i = 0; i < n; narr[i] = darr[i], i++);
	count = n;
	return narr;
}

int main(void) {

	calcTime("selection sorting took %f seconds.\n", {
		int len;
		int *arr = genDataArr(len);
		printf("curr array at %p\n", arr);
		selectSort(arr, len);
		printArr(arr, len);
		delete arr;
	});
	puts("");

	calcTime("selection sorting took %f seconds.\n", {
		int len;
		int *arr = genDataArr(len);
		printf("curr array at %p\n", arr);
		selectSort(arr, len);
		printArr(arr, len);
		delete arr;
	});

	return 0;
}
