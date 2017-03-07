/**
 *  @file gen_data.cpp
 *  @author Sheng-Hao Ma (aaaddress1, aka adr)
 *  @date 03/07/2017
 *  @brief data generator for testing software
 **/

int* genDataArr(int &count) {
	static int darr[] = {999, 1, 7, 3, 2, 9, 22, 8, 0, 5}; //input array data
	static int n = sizeof(darr) / sizeof(int); //array length
	int *narr = new int[n];
	for (int i = 0; i < n; narr[i] = darr[i], i++);
	count = n;
	return narr;
}