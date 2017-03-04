/**
 * 	@file sorting.cpp
 * 	@author Sheng-Hao Ma (aaaddress1, aka adr)
 * 	@date 03/05/2017
 * 	@brief implementat sorting algoprithms
 **/
#include <stdio.h>
#include <algorithm>
#include <time.h>
#define printArr(a, n) { for(size_t i = 0; i < n; printf("%d ", a[i]), i++); }

/* Selection Sorting */
void selectSort(/* input array */int *a, /* count */size_t n) {
	#define swap(type, x, y) { type buff = x; x = y; y = buff; }
	for(int i = 0, j = 0, p = 0; i < n - 1; i++) {
		p = i;
		for(j = i + 1; j < n; j++) p = a[p] < a[j] ? p : j;
		swap(int, a[p], a[i]);
	}
}

/* Merge Sorting */
void merge(/* input array */int *a, /* left array count */size_t n1, /* right array count */size_t n2) {
	int n(n1 + n2);
	int *tmp(new int[n]);
	int *left_a(a), *right_a(a + n1);

	for (int pos = 0; pos < n; pos++) 
		if ((left_a >= (a + n1)) && (right_a < a + n1 + n2))
			tmp[pos] = *(right_a++);
		else if ((right_a >= (a + n1 + n2)) && (left_a < a + n1))
			tmp[pos] = *(left_a++);
		else if (*left_a < *right_a)
			tmp[pos] = *(left_a++);
		else
			tmp[pos] = *(right_a++);

	for (int pos = 0; pos < (n1 + n2); pos++)
		a[pos] = tmp[pos];
}

void mergeSortRecur(/* input array */int *a, /* count */size_t n) {
	if (n <= 1) return;
	int half_len = n / 2;
	mergeSortRecur(a, half_len);
	mergeSortRecur((a + half_len), (n - half_len));
	merge(a, half_len, (n - half_len));
}

void mergeSortItera(/* input array */int *a, /* count */size_t n) {
	for (int item_cnt = 1;item_cnt < n; item_cnt *= 2)
		for (int i = 0; i < n; i += item_cnt *2) {
			if (i + item_cnt > n) break;
			merge(a + i, item_cnt, (n-i-item_cnt) > item_cnt ? item_cnt : n-i-item_cnt);
		}
}

/* generate data for testing */
int* genDataArr(int &count) {
	static int darr[] = {999, 1, 7, 3, 2, 9, 22, 8, 0, 5}; //input array data
	static int n = sizeof(darr) / sizeof(int); //array length
	int *narr = new int[n];
	for (int i = 0; i < n; narr[i] = darr[i], i++);
	count = n;
	return narr;
}

int main(void) {
	#define sortClock(data, len, sortName, body) { \
		int len, *arr = genDataArr(len); \
		puts(sortName); \
		printf("\t- data: \n\t\t"); printArr(arr, len); puts(""); \
		clock_t b = clock(); \
		body; \
		printf("\t- %s took %f seconds.\n", sortName, ((float)(clock() - b)/CLOCKS_PER_SEC)); \
		printf("\t- data after sort: \n\t\t"); printArr(arr, len); puts("\n"); \
		delete arr; \
	}
	sortClock(arr, len, "Selection Sort", { selectSort(arr, len); });
	sortClock(arr, len, "Recursive Merge Sort", { mergeSortRecur(arr, len); });
	sortClock(arr, len, "Iterative Merge Sort", { mergeSortItera(arr, len); });
	return 0;
}
