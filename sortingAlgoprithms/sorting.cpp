/**
 * 	@file sorting.cpp
 * 	@author Sheng-Hao Ma (aaaddress1, aka adr)
 * 	@date 03/07/2017
 * 	@brief implementat sorting algoprithms and figure out performance
 **/
#include <stdio.h>
#include <time.h>
#include "heap_sort.cpp"
#include "merge_sort.cpp"
#include "data_gentr.cpp"
#define printArr(a, n) { for(size_t i = 0; i < n; printf("%d ", a[i]), i++); }

void insertSort(/* input array */int *a, /* count */size_t n) {
	for (int i = 1, j, t; i < n; i++) {
		for(t = a[i], j = i; j --> -1; a[j + 1] = a[j])
			if (a[j] < t) break;
		a[j + 1] = t;
	}
}

int main(void) {
	#define sortClock(data, len, sortName, body) { \
		int len, *arr = genDataArr(len); puts(sortName); \
		printf("\t- data: \n\t\t"); printArr(arr, len); puts(""); \
		clock_t b = clock(); \
		body; \
		printf("\t- %s took %f seconds.\n", sortName, ((float)(clock() - b)/CLOCKS_PER_SEC)); \
		printf("\t- data after sort: \n\t\t"); printArr(arr, len); puts("\n"); \
		delete arr; \
	}

	sortClock(arr, len, "Insertion Sort", { insertSort(arr, len); });
	sortClock(arr, len, "Recursive Merge Sort", { mergeSortRecur(arr, len); });
	sortClock(arr, len, "Iterative Merge Sort", { mergeSortItera(arr, len); });
	sortClock(arr, len, "Heap Sort", { mergeSortItera(arr, len); });
	return 0;
}
