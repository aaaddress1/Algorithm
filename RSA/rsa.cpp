/**
 * @file rsa.cpp
 * @author 10303118a
 * @date 2017/03/01
 **/
#include <stdio.h>
#include <cstdlib>
#include <math.h>

bool get_inverse(int n, int a, int &inv_buff) {
	#define MAX_LEN 100

	int quotient[MAX_LEN], remainder[MAX_LEN], s[MAX_LEN], t[MAX_LEN];
	remainder[0] = n, remainder[1] = a, s[0] = 1, s[1] = 0, t[0] = 0, t[1] = 1;
	for(int i = 2;; i++) {
		quotient[i] = remainder[i-2] / remainder[i-1];
		remainder[i] = remainder[i-2] - quotient[i] * remainder[i-1];
		s[i] = s[i-2] - quotient[i] * s[i-1];
		t[i] = t[i-2] - quotient[i] * t[i-1];
		if (!remainder[i]) {
			inv_buff = t[i-1];
			return true;
		}
		if (remainder[i] < 0) break;
	}
	return false;
}

int main(void) {
	int p, q, n ,phi, e, d;
	p = 5, q = 7;
	n = p * q;
	phi = (p - 1) * (q - 1);
	printf("n = %i; 1 < e < %i\n", n, phi);

	// generate e and d
	e = 7;
	if (!get_inverse(phi, e, d)) {
		puts("get inverse d fail.");
		return 0;
	}
	
	printf("e = %i, d = %i\n", e, d);

	// init for array (secret and data)
	int m[] = {1, 2, 3, 4, 5, 6};
	int length = sizeof(m) / sizeof(int);
	int *c = new int[length];

	//encrypt
	for(int i = 0; i < length; i++)
		c[i] = (int)fmod(pow(m[i], e), n);
	printf("current secret array: ");
	for(int i = 0; i < length; i++)
		printf("%i ", c[i]);
	puts("");

	// decrypt
	for(int i = 0; i < length; i++)
		c[i] = (int)fmod(pow(c[i], d), n);
	printf("current data array: ");
	for(int i = 0; i < length; i++)
		printf("%i ", c[i]);
	puts("");
	return 0;
}
