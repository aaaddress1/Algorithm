/**
 *  @file heap_sort.cpp
 *  @author Sheng-Hao Ma (aaaddress1, aka adr)
 *  @date 03/07/2017
 *  @brief implementat sorting algoprithms and figure out performance
 **/
#include <stdio.h>      /* printf, scanf, puts */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time, clock_t, clock */
#include "heap_sort.cpp"
#include "merge_sort.cpp"

int* dataGenor(int count) {
	int c = count, *narr = new int[count];
	srand(time(0));
	for (; c-->0; narr[c] = rand() % 100000);
	return narr;
}

void insertSort(/* input array */int *a, /* count */int n) {
	for (int i = 1, tmp = 0, j = 0; i < n; i++) {
		for (tmp = a[i], j = i-1;j >= 0 && a[j] > tmp;) {
			a[j+1] = a[j];
			j = j-1;
		}
	a[j+1] = tmp;
}
}

int main(void) {
	int dataDB[] = { 10000, 50000, 100000, 150000, 200000, 250000 };
	#define dataDBLen (sizeof dataDB / sizeof *dataDB)
	#define sortTypeLen (4)
	char(*sortNm[sortTypeLen]) = { "insertion sort", "recursive merge sort", "iterative merge sort", "heap sort" };
	void(*funcPtr[sortTypeLen])(int*, int) = { insertSort, mergeSortRecur, mergeSortItera, heapSort };

	/* open file for logs */
	FILE *fp = fopen("output.txt", "w");
	if (!fp) {
		puts("output file open fail.");
		return 0;
	}

	/* print table header */
	fprintf(fp, "%20s\t", "");
	for (int i = 0; i < dataDBLen; i++) fprintf(fp, "%8d\t", dataDB[i]);
	fputs("\n", fp);

	/* print single list for each sortting algoprithm */
	for (int mode = 0; mode < sortTypeLen; mode++) {
		fprintf(fp, "%20s\t", sortNm[mode]);
		for (int i = 0; i < dataDBLen; i++) {
			printf("%s is sortting %d numbers.\n", sortNm[mode], dataDB[i]);
			int *dataArr = dataGenor(dataDB[i]);
			clock_t b = clock();
			(*funcPtr[mode])(dataArr, dataDB[i]);
			fprintf(fp, "%8.3f s\t", (float)(clock() - b) / CLOCKS_PER_SEC);
			printf("%s took %5.3f s to sort %d numbers.\n", sortNm[mode], (float)(clock() - b) / CLOCKS_PER_SEC, dataDB[i]);
		}
		puts("");
		fputs("\n", fp);
	}
	fclose(fp);
	puts("result table have been saved sucessfully in 'output.txt'!");
	system("PAUSE");
	return 0;
}
