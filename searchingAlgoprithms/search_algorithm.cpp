/**
 * 	@file search_algorithm.cpp
 * 	@author Sheng-Hao Ma (aaaddress1, aka adr)
 * 	@date 04/14/2017
 * 	@brief implementat searching algoprithms and figure out performance
 **/
#include <stdio.h>
#include <stdlib.h> 	/* srand, rand */
#include <deque>		/* std::deque  */
#include <string>		/* std::string */
#include <algorithm> 	/* std::sort   */

std::deque<std::string> dataGenor(int count) {
	const char alphabet_list[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const int alphabet_list_len = (sizeof(alphabet_list) / sizeof(char)) - 1;
	std::deque<std::string> retn_que;
	srand(time(NULL));
	while (count--) {
		std::string tmpStr = "";
		for (int i = 0; i < 6; i++)
			tmpStr += alphabet_list[rand() % alphabet_list_len];
		retn_que.push_back(tmpStr);
	}
	return retn_que;
}

/**
 * @function sortStrData
 *
 * @brief sorting strings in the deque via ASCII value and length
 * (this implement can be replaced by std::sort)
 **/
void sortStrData(std::deque<std::string> &arr) {
	struct {
		bool operator() (std::string s1, std::string s2) {
			for (int i = 0; i < s1.length() && i < s2.length(); i++)
				if (s1[i] != s2[i])
					return s1[i] < s2[i];
			return s1.length() == s2.length() ? false : s1.length() < s2.length();
		}
	} compareFunc;
	std::sort(arr.begin(), arr.end(), compareFunc);
}

int iterBinarySearch(std::deque<std::string> array, std::string str) {
	int left = 0, right = array.size() - 1, middle;

	while (left <= right) {
		middle = (right + left) / 2;

		if (!array[middle].compare(str))
			return middle;
		for (int i = 0; i < array[middle].length() && i < str.length(); i++) {
			if (array[middle][i] == str[i])
				continue;
			if (array[middle][i] > str[i])
				right = middle - 1;
			else
				left = middle + 1;
			break;
		}

	}
	return -1;
}

int recuBinarySearch(std::deque<std::string> array, std::string str, int left, int right) {
	int middle = (right + left) / 2;

	if (left > right)
		return -1;

	if (!array[middle].compare(str))
		return middle;
	for (int i = 0; i < array[middle].length() && i < str.length(); i++) {
		if (array[middle][i] == str[i])
			continue;
		if (array[middle][i] > str[i])
			right = middle - 1;
		else
			left = middle + 1;
		break;
	}
	return recuBinarySearch(array, str, left, right);
}

int hashStr(std::string s) {
	int cHash = 0, p = 0;
	while (p < s.length()) cHash += s[p++];
	return cHash;
}

static clock_t b;
#define time_break_point() ({ b = clock(); })
#define time_stop__alert(msg) ({ printf("%f\n", (float)(clock() - b)/CLOCKS_PER_SEC); })

int main(void) {
	const std::string target_str = "ACvmZe";

	std::deque<std::string> rnd_data = dataGenor(10000);
	std::deque<std::string> iter_bin_data(rnd_data.begin(), rnd_data.end());
	std::deque<std::string> recu_bin_data(rnd_data.begin(), rnd_data.end());
	std::deque<std::string> hashtabl_data(rnd_data.begin(), rnd_data.end());
	
	/* iterative binary search */
	time_break_point();
	std::sort(iter_bin_data.begin(), iter_bin_data.end());
	time_stop__alert("iterative binary search (sorting)");
	time_break_point();
	iterBinarySearch(iter_bin_data, target_str);
	time_stop__alert("iterative binary search (search)");

	/* recursive binary search */
	time_break_point();
	std::sort(recu_bin_data.begin(), recu_bin_data.end());
	time_stop__alert("recursive binary search (sorting)");
	time_break_point();
	recuBinarySearch(recu_bin_data, target_str, 0, recu_bin_data.size() - 1);
	time_stop__alert("recursive binary search (search)");

	/* hashing table search */
	const int groupCount = 26;
	std::deque<std::string> hashTable[groupCount];

	time_break_point();
	for (int i = 0, p = 0; i < hashtabl_data.size(); i++) {
		p = hashStr(hashtabl_data[i]) % groupCount;
		hashTable[p].push_front(hashtabl_data[i]);
	}
	time_stop__alert("hashing table search (create table)");
	time_break_point();
	int pos = hashStr(target_str) % groupCount;
	for (int i = 0; i < hashTable[pos].size(); i++)
		if (!hashTable[pos][i].compare(target_str))
			break;

	time_stop__alert("hashing table search (search)");

	return 0;
}
