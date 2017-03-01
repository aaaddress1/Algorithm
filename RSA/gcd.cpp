/**
 * @file gcd.cpp
 * @author 10303118a
 * @date 2017/03/01
 **/
#include <stdio.h>
#define MAX_LEN (100)
int main(void) {
	int quotient[MAX_LEN], remainder[MAX_LEN], s[MAX_LEN], t[MAX_LEN];

	remainder[0] = 240, remainder[1] = 46, s[0] = 1, s[1] = 0, t[0] = 0, t[1] = 1;
	for(int i = 2;; i++) {
		quotient[i] = remainder[i-2] / remainder[i-1];
		remainder[i] = remainder[i-2] - quotient[i] * remainder[i-1];
		s[i] = s[i-2] - quotient[i] * s[i-1];
		t[i] = t[i-2] - quotient[i] * t[i-1];
		printf("index = %d |\t q[i-1] = %d, r[i] = %d, s[i] = %d, t[i] = %d\n", i, quotient[i], remainder[i], s[i], t[i]);
		if (!remainder[i]) {
			printf("gcd(%d, %d) = %d, found successfully!", remainder[0], remainder[1], t[i-1]);
			break;
		}
		if (i > 100) {
			printf("gcd(%d, %d) resault found fail in 100 steps.", remainder[0], remainder[1]);
			break;
		}
	}
	return 0;
}
