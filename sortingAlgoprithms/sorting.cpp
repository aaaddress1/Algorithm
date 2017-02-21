/**
 * 	@file sorting.cpp
 * 	@author Sheng-Hao Ma (aaaddress1, aka adr)
 * 	@date 02/21/2017
 * 	@brief implementat sorting algoprithms
 **/
#include <stdio.h>
#include <algorithm>
#include <time.h>
#define swap(type, x, y) do{ type buff = x; x = y; y = buff; } while(0)
#define calcTime(entermsg, msg, body) { puts(entermsg); clock_t b = clock(); body; printf(msg, ((float)(clock() - b)/CLOCKS_PER_SEC)); }


void printArr(/* output array */int *a, /* count */size_t n) {
	for(size_t i = 0; i < n; printf("%d ", a[i]), i++);
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
void merge(/* input array */int *a, /* left array count */size_t n1, /* right array count */size_t n2) {
	int n(n1 + n2);
	int *tmp(new int[n]);
	int *left_a(a), *right_a(a + n1);
	std::sort(left_a, right_a);
	std::sort(right_a, right_a + n2);

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

void mergeSort(/* input array */int *a, /* count */size_t n) {
	if (n <= 1) return;
	int half_len = n / 2;
	mergeSort(a, half_len);
	mergeSort((a + half_len), (n - half_len));
	merge(a, half_len, (n - half_len));
}

/* generate data for testing */
int* genDataArr(int &count) {
	static int darr[] = {999, 1, 7, 3, 2, 5, 11, 20 , 7, 99, 8, 22, 1000}; //input array data
	static int n = sizeof(darr) / sizeof(int); //array length
	int *narr = new int[n];
	for (int i = 0; i < n; narr[i] = darr[i], i++);
	count = n;
	return narr;
}

int main(void) {
	int len, *arr;

	arr = genDataArr(len);
	calcTime(	"/* === selection sorting case === */",
				"selection sorting took %f seconds.\n", {
		printf("curr array at %p\n", arr);
		puts("curr array: "); printArr(arr, len); puts("");
		selectSort(arr, len);
		puts("curr array: "); printArr(arr, len); puts("");
		delete arr;
	});
	puts("");

	arr = genDataArr(len);
	calcTime(	"/* === merge sorting case === */",
				"merge sorting took %f seconds.\n", {
		printf("curr array at %p\n", arr);
		puts("curr array: "); printArr(arr, len); puts("");
		mergeSort(arr, len);
		puts("curr array: "); printArr(arr, len); puts("");
		delete arr;
	});

	return 0;
}
