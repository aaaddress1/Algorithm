/**
 * 	@file sorting.cpp
 * 	@author Sheng-Hao Ma (aaaddress1, aka adr)
 * 	@date 03/07/2017
 * 	@brief implementat sorting algoprithms and figure out performance
 **/
#include <stdio.h>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include "heap_sort.cpp"
#include "merge_sort.cpp"

#define printArr(a, n) { for(size_t i = 0; i < n; printf("%d ", a[i]), i++); }
#define calcClock(body) ({ clock_t b = clock(); body; (float)(clock() - b)/CLOCKS_PER_SEC; })
#define dataGenor(count) ({ int c = count, *narr = (int *)malloc(sizeof(int) * count); for(; c-->0; narr[c] = rand() % 100000); narr; })

void insertSort(/* input array */int *a, /* count */size_t n) {
	for (int i = 1, j, t; i < n; i++) {
		for(t = a[i], j = i; j >= 0 && a[j] > t; a[j + 1] = a[j], j--);
		a[j + 1] = t;
	}
}

int main(void) {

	int dataDB[] = { 10000, 50000, 100000, 150000, 200000, 250000 };
	int dataDBLen = sizeof dataDB / sizeof *dataDB;

	printf("%20s\t","");
	for(int i = 0; i < dataDBLen; i++)
		printf("%10d %s\t", dataDB[i], "筆");
	puts("");

	printf("%20s\t", "insertion sort");
	for (int i = 0; i < dataDBLen; i++) {
		int *dataArr = dataGenor(dataDB[i]);
		float t = calcClock({ insertSort(dataArr, dataDB[i]); });
		printf("%10f %s\t", t, "秒");
		free(dataArr);
	}
	puts("");
	
	printf("%20s\t", "recursive merge sort");
	for (int i = 0; i < dataDBLen; i++) {
		int *dataArr = dataGenor(dataDB[i]);
		float t = calcClock({ mergeSortRecur(dataArr, dataDB[i]); });
		printf("%10f %s\t", t, "秒");
		free(dataArr);
	}
	puts("");

	printf("%20s\t", "iterative merge sort");
	for (int i = 0; i < dataDBLen; i++) {
		int *dataArr = dataGenor(dataDB[i]);
		float t  = calcClock({ mergeSortItera(dataArr, dataDB[i]); });
		printf("%10f %s\t", t, "秒");
		free(dataArr);
	}
	puts("");

	printf("%20s\t", "heap sort");
	for (int i = 0; i < dataDBLen; i++) {
		int *dataArr = dataGenor(dataDB[i]);
		float t = calcClock({ heapSort(dataArr, dataDB[i]); });
		printf("%10f %s\t", t, "秒");
		free(dataArr);
	}
	puts("");
	return 0;
}
