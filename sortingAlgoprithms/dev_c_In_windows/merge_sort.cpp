/**
 *  @file merge_sort.cpp
 *  @author Sheng-Hao Ma (aaaddress1, aka adr)
 *  @date 03/07/2017
 *  @brief implementat merge sorting algoprithms
 **/

void merge(/* input array */int *a, /* left array count */int n1, /* right array count */int n2) {
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

void mergeSortRecur(/* input array */int *a, /* count */int n) {
	if (n <= 1) return;
	int half_len = n / 2;
	mergeSortRecur(a, half_len);
	mergeSortRecur((a + half_len), (n - half_len));
	merge(a, half_len, (n - half_len));
}

void mergeSortItera(/* input array */int *a, /* count */int n) {
	for (int item_cnt = 1;item_cnt < n; item_cnt *= 2)
		for (int i = 0; i < n; i += item_cnt *2) {
			if (i + item_cnt > n) break;
			merge(a + i, item_cnt, (n-i-item_cnt) > item_cnt ? item_cnt : n-i-item_cnt);
		}
}
